#!/usr/bin/env python3
"""
Mid360 建图脚本 —— 3D 点云（体素降采样 0.15）+ 2D 栅格地图 + 打点。

用法：
    source /opt/ros/jazzy/setup.bash
    source ~/ws_livox/install/setup.bash
    python3 demo_mid360_mapping_full.py

流程：
    1. 起 Livox 驱动 + Super-LIO 建图（ros2 launch super_lio Livox_mid360.py）
    2. 跑本脚本，推车扫图
    3. 启动时【自动记录起始位置+朝向】到 point_origin.txt
    4. 推车到目标位置，输入 g 记录目标点（坐标+朝向）到 point_targets.txt
    5. 按 q 退出，保存两张图：
       - map3d.pcd（三维点云，体素 0.15 降采样）
       - map2d.pgm + map2d.yaml（二维栅格地图，Nav2 用）

原理：
    - 订阅 Super-LIO 的 /lio/cloud_world（world 坐标点云）
    - 边累积边体素降采样（0.15m，每个体素只留一个点，省内存）
    - 3D 点云投影到 XY 平面，栅格化成 2D 占用栅格（Nav2 标准 PGM+YAML）
    - 打点坐标是 LIO world 坐标，重定位对齐后就是地图坐标
"""

import math
import subprocess
import threading
import time
from datetime import datetime

import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from nav_msgs.msg import Odometry, OccupancyGrid
from sensor_msgs.msg import PointCloud2
from sensor_msgs_py import point_cloud2

# ==================== 配置 ====================
CLOUD_TOPIC = "/lio/cloud_world"        # Super-LIO 的 world 点云话题
ROBOT_ODOM_TOPIC = "/lio/robo/odom"     # 机器人位姿话题

VOXEL_SIZE = 0.15       # 体素降采样尺寸（米）
GRID_RES = 0.05         # 2D 栅格分辨率（米）
GRID_MIN_H = 0.1        # 2D 栅格取点的高度下限（过滤地面）
GRID_MAX_H = 2.0        # 2D 栅格取点的高度上限（过滤天花板）

POINTS_FILE = "/home/slam/r2_ws/test_demo/points.txt"   # 点位（origin 起始 + target 目标点）
MAP3D_FILE = "/home/slam/r2_ws/test_demo/map3d.pcd"     # 3D 点云
MAP2D_PGM = "/home/slam/r2_ws/test_demo/map2d.pgm"      # 2D 栅格图
MAP2D_YAML = "/home/slam/r2_ws/test_demo/map2d.yaml"    # 2D 栅格元数据
MAP2D_PNG = "/home/slam/r2_ws/test_demo/map2d.png"      # 2D 栅格图 PNG（预览用）


def quat_to_yaw(qx, qy, qz, qw):
    return math.atan2(2.0 * (qw * qz + qx * qy), 1.0 - 2.0 * (qy * qy + qz * qz))


# ==================== 建图节点 ====================

class MappingNode(Node):
    def __init__(self):
        super().__init__("mid360_mapping_full")
        self._lock = threading.Lock()
        # 3D 体素栅格 {(gx, gy, gz): (x, y, z)}，边累积边降采样
        self.voxel_grid = {}
        self.frame_count = 0
        # 机器人位姿
        self._rx = 0.0
        self._ry = 0.0
        self._ryaw = 0.0
        self._rstamp = 0.0
        # 打点
        self.origin = None
        self.targets = []

        self.create_subscription(PointCloud2, CLOUD_TOPIC, self._cloud_cb, 10)
        self.create_subscription(Odometry, ROBOT_ODOM_TOPIC, self._odom_cb, 10)
        # 实时发布 2D 占用栅格（Nav2 约定）
        self.grid_pub = self.create_publisher(OccupancyGrid, "/mapping_grid", 1)
        self.create_timer(2.0, self.publish_grid)
        print(f"✅ 订阅：点云 {CLOUD_TOPIC}，位姿 {ROBOT_ODOM_TOPIC}")

    def _cloud_cb(self, msg: PointCloud2):
        """累积点云，边累积边体素降采样 0.15。"""
        inv = 1.0 / VOXEL_SIZE
        with self._lock:
            for p in point_cloud2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True):
                x, y, z = float(p[0]), float(p[1]), float(p[2])
                key = (int(x * inv), int(y * inv), int(z * inv))
                if key not in self.voxel_grid:
                    self.voxel_grid[key] = (x, y, z)
        self.frame_count += 1
        if self.frame_count % 50 == 0:
            print(f"  已累计 {len(self.voxel_grid):,} 个体素（{self.frame_count} 帧）")

    def _odom_cb(self, msg: Odometry):
        p = msg.pose.pose
        with self._lock:
            self._rx = float(p.position.x)
            self._ry = float(p.position.y)
            self._ryaw = quat_to_yaw(p.orientation.x, p.orientation.y,
                                     p.orientation.z, p.orientation.w)
            self._rstamp = time.time()

    def get_pose(self):
        with self._lock:
            return self._rx, self._ry, self._ryaw, self._rstamp

    def get_cloud(self):
        with self._lock:
            return list(self.voxel_grid.values())

    def publish_grid(self):
        """实时发布 2D 占用栅格（Nav2 约定：0=自由，100=占用，-1=未知）。"""
        pts = self.get_cloud()
        if not pts:
            return
        xy = [(x, y) for x, y, z in pts if GRID_MIN_H <= z <= GRID_MAX_H]
        if not xy:
            return
        xs = [p[0] for p in xy]
        ys = [p[1] for p in xy]
        min_x, max_x = min(xs), max(xs)
        min_y, max_y = min(ys), max(ys)
        cols = int((max_x - min_x) / GRID_RES) + 1
        rows = int((max_y - min_y) / GRID_RES) + 1

        data = [0] * (cols * rows)  # 0=自由
        for x, y in xy:
            c = int((x - min_x) / GRID_RES)
            r = int((y - min_y) / GRID_RES)
            if 0 <= c < cols and 0 <= r < rows:
                data[r * cols + c] = 100  # 100=占用

        msg = OccupancyGrid()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "world"
        msg.info.resolution = GRID_RES
        msg.info.width = cols
        msg.info.height = rows
        msg.info.origin.position.x = min_x
        msg.info.origin.position.y = min_y
        msg.info.origin.position.z = 0.0
        msg.info.origin.orientation.w = 1.0
        msg.data = data
        self.grid_pub.publish(msg)

    # ---- 保存 ----

    def save_3d_pcd(self, path):
        pts = self.get_cloud()
        if not pts:
            print("❌ 没有点")
            return False
        with open(path, "w") as f:
            f.write("# .PCD v0.7 - Point Cloud Data file format\n")
            f.write("VERSION 0.7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1\n")
            f.write(f"WIDTH {len(pts)}\nHEIGHT 1\nVIEWPOINT 0 0 0 1 0 0 0\n")
            f.write(f"POINTS {len(pts)}\nDATA ascii\n")
            for x, y, z in pts:
                f.write(f"{x:.6f} {y:.6f} {z:.6f}\n")
        print(f"✅ 3D 点云已保存：{path}（{len(pts):,} 个点，体素 {VOXEL_SIZE}m）")
        return True

    def save_2d_grid(self, pgm_path, yaml_path):
        """把 3D 点云投影到 XY，栅格化成 2D 占用栅格（Nav2 格式）。"""
        pts = self.get_cloud()
        # 取高度范围内的点（过滤地面/天花板）
        xy = [(x, y) for x, y, z in pts if GRID_MIN_H <= z <= GRID_MAX_H]
        if not xy:
            print("❌ 高度范围内没有点，无法生成 2D 栅格")
            return False
        xs = [p[0] for p in xy]
        ys = [p[1] for p in xy]
        min_x, max_x = min(xs), max(xs)
        min_y, max_y = min(ys), max(ys)

        cols = int((max_x - min_x) / GRID_RES) + 1
        rows = int((max_y - min_y) / GRID_RES) + 1
        # 占用栅格：0=占用(黑/障碍) 254=空闲(白)，Nav2 标准约定
        grid = [[254] * cols for _ in range(rows)]
        for x, y in xy:
            c = int((x - min_x) / GRID_RES)
            r = int((y - min_y) / GRID_RES)
            if 0 <= c < cols and 0 <= r < rows:
                grid[r][c] = 0

        # 写 PGM（图像坐标系 y 反向）
        with open(pgm_path, "w") as f:
            f.write("P2\n")
            f.write(f"{cols} {rows}\n255\n")
            for r in range(rows - 1, -1, -1):
                f.write(" ".join(str(grid[r][c]) for c in range(cols)) + "\n")

        # 写 YAML（Nav2 元数据，注意 origin 是左下角坐标）
        origin_x = min_x
        origin_y = min_y
        with open(yaml_path, "w") as f:
            f.write(f"image: {MAP2D_PGM}\n")
            f.write(f"resolution: {GRID_RES}\n")
            f.write(f"origin: [{origin_x:.3f}, {origin_y:.3f}, 0.0]\n")
            f.write("negate: 0\n")
            f.write("occupied_thresh: 0.65\n")
            f.write("free_thresh: 0.196\n")

        # 写 PNG（预览用，障碍黑、空地白，图像坐标系 y 反向）
        try:
            from PIL import Image
            img = Image.new("L", (cols, rows), 255)
            px = img.load()
            for r in range(rows):
                for c in range(cols):
                    px[c, rows - 1 - r] = 0 if grid[r][c] == 0 else 255
            img.save(MAP2D_PNG)
            print(f"✅ 2D 栅格 PNG 已保存：{MAP2D_PNG}")
        except ImportError:
            print("⚠️ 未安装 Pillow，跳过 PNG 保存")

        print(f"✅ 2D 栅格已保存：{pgm_path} + {yaml_path}（{cols}x{rows}，分辨率 {GRID_RES}m）")
        return True

    def save_points(self):
        with open(POINTS_FILE, "w") as f:
            if self.origin is not None:
                f.write(f"origin {self.origin[0]:.6f} {self.origin[1]:.6f} {self.origin[2]:.4f}\n")
            for x, y, yaw in self.targets:
                f.write(f"target {x:.6f} {y:.6f} {yaw:.4f}\n")
        print(f"✅ 点位已保存：{POINTS_FILE}（起始 {1 if self.origin else 0} 个，目标 {len(self.targets)} 个）")


def launch_rviz():
    """启动一个 RViz 小窗口，展示 2D 栅格地图（/mapping_grid，渲染轻、不卡）。"""
    rviz_config = "/home/slam/r2_ws/test_demo/mapping_grid.rviz"
    cmd = (f"source /opt/ros/humble/setup.bash && "
           f"source /home/slam/r2_ws/lidar_ws/install/setup.bash && "
           f"ros2 run rviz2 rviz2 -d {rviz_config}")
    return subprocess.Popen(["bash", "-c", cmd],
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)


def main():
    rclpy.init()
    node = MappingNode()
    executor = SingleThreadedExecutor()
    executor.add_node(node)
    threading.Thread(target=executor.spin, daemon=True).start()

    # 等定位就绪，自动记录起始位置
    print("等待定位 ...")
    t0 = time.time()
    while time.time() - t0 < 5.0:
        if node.get_pose()[3] > 0:
            break
        time.sleep(0.1)
    else:
        print("❌ 5 秒没收到定位")
        return
    x, y, yaw, _ = node.get_pose()
    node.origin = (x, y, math.degrees(yaw))
    print(f"✅ 已自动记录起始位置：x={x:.3f} y={y:.3f} yaw={math.degrees(yaw):.1f}°\n")

    # 启动 RViz 小窗口展示栅格地图
    print("启动 RViz 窗口展示建图地图...")
    launch_rviz()

    print("=" * 55)
    print("Mid360 建图模式")
    print("  g = 记目标点   l = 列表   q = 退出并保存")
    print("=" * 55)

    try:
        while True:
            x, y, yaw, _ = node.get_pose()
            print(f"\r  位置 x={x:.3f} y={y:.3f} yaw={math.degrees(yaw):.1f}°  "
                  f"体素 {len(node.voxel_grid):,}  输入：", end="", flush=True)
            try:
                cmd = input().strip()
            except (EOFError, KeyboardInterrupt):
                cmd = "q"

            if cmd == "g":
                x, y, yaw, _ = node.get_pose()
                node.targets.append((x, y, math.degrees(yaw)))
                print(f"\n✅ 目标点 #{len(node.targets)}：x={x:.3f} y={y:.3f} yaw={math.degrees(yaw):.1f}°")
            elif cmd == "l":
                print(f"\n起始：{node.origin}")
                for i, t in enumerate(node.targets, 1):
                    print(f"目标 #{i}：x={t[0]:.3f} y={t[1]:.3f} yaw={t[2]:.1f}°")
            elif cmd == "q":
                break
            else:
                print("\ng=记点  l=列表  q=退出保存")
    except KeyboardInterrupt:
        print("\nCtrl+C，保存退出")

    # 保存两张图 + 打点
    print("\n正在保存...")
    node.save_3d_pcd(MAP3D_FILE)
    node.save_2d_grid(MAP2D_PGM, MAP2D_YAML)
    node.save_points()
    print("✅ 全部保存完成")

    executor.shutdown()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
