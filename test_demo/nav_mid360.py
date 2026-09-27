#!/usr/bin/env python3
"""
Mid360 导航脚本 —— Nav2 绕障规划 + PID 导航（由 nav.launch.py 启动）。

用法（一个 launch 文件启动 驱动 + Super-LIO 重定位 + Nav2 + 本脚本）：
    source /opt/ros/humble/setup.bash
    source ~/r2_ws/lidar_ws/install/setup.bash
    ros2 launch /home/slam/r2_ws/test_demo/nav.launch.py

注意：雷达需按"先启动、后上电"顺序（先跑本命令，再给雷达上电），否则驱动可能握不上手。

交互流程：
    1. Nav2 已由 launch 加载地图 + 绕障规划器 + TF 桥
    2. 打印起始坐标、目标点坐标
    3. 询问"是否开始导航至目标点位"，按 y 确认后开始
    4. 用 Nav2 规划绕障路径，PID 逐个路径点走到目标

PID 控制（参考 usc move_to_target）：
    每周期读当前位置，算偏差 → 转到车体系 → 比例控制 → ch0/ch2 速度
"""

import math
import socket
import struct
import threading
import time

import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from rclpy.action import ActionClient
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import ComputePathToPose

# ==================== 网络 / 话题 ====================
TCP_IP = "192.168.2.199"
TCP_PORT = 5000
ROBOT_ODOM_TOPIC = "/lio/robo/odom"
POINTS_FILE = "/home/slam/r2_ws/test_demo/points.txt"
PLAN_ACTION = "/compute_path_to_pose"

# ==================== 帧常量（和 usc 一致）====================
SOF1 = 0xA5
SOF2 = 0x5A
LEN = 0x1C
TYPE = 0x01
SAFE_SWITCH = 1
FRAME_HZ = 70

# ==================== PID 参数（参考 usc move.py）====================
PID_KP = 800.0           # 位置比例增益（速度 = kp * 距离，再限幅）
PID_MAX_SPEED = 190      # 最大速度（ch0/ch2 限幅）
STOP_DISTANCE = 0.05     # 到达判定距离（米）
TURN_TOL_DEG = 2.0       # 转向到位容差（度）
TURN_GAIN = 1.0          # 转向速度放大倍数（>1 转更快，但误差大会绕反方向，慎改）


def crc16_ccitt(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= (byte << 8)
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
    return crc


def build_frame(seq, channels, yaw=0, des_yaw=0, cylinder=0):
    payload = struct.pack("<H", seq & 0xFFFF)
    for ch in channels:
        payload += struct.pack("<h", max(-32768, min(32767, int(ch))))
    payload += struct.pack("<h", yaw)
    payload += struct.pack("<h", des_yaw)
    payload += struct.pack("<h", cylinder)
    crc = crc16_ccitt(bytes([LEN, TYPE]) + payload)
    return bytes([SOF1, SOF2, LEN, TYPE]) + payload + struct.pack("<H", crc)


def motion_channels(lateral=0, forward=0, rotation=0):
    ch = [0, 0, 0, 0] + [SAFE_SWITCH] * 6
    ch[0] = int(lateral)
    ch[2] = int(forward)
    ch[3] = int(rotation)
    return ch


def quat_to_yaw(qx, qy, qz, qw):
    return math.atan2(2.0 * (qw * qz + qx * qy), 1.0 - 2.0 * (qy * qy + qz * qz))


def norm_deg(d):
    while d > 180.0:
        d -= 360.0
    while d < -180.0:
        d += 360.0
    return d


def yaw_deg_to_i16(d):
    return int(round(d * 100.0))


# ==================== 定位节点 ====================

class Localizer(Node):
    def __init__(self):
        super().__init__("mid360_nav_localizer")
        self._lock = threading.Lock()
        self._x = 0.0
        self._y = 0.0
        self._yaw = 0.0
        self._stamp = 0.0
        self.create_subscription(Odometry, ROBOT_ODOM_TOPIC, self._cb, 10)

    def _cb(self, msg):
        p = msg.pose.pose
        with self._lock:
            self._x = float(p.position.x)
            self._y = float(p.position.y)
            self._yaw = quat_to_yaw(p.orientation.x, p.orientation.y,
                                    p.orientation.z, p.orientation.w)
            self._stamp = time.time()

    def get_pose(self):
        with self._lock:
            return self._x, self._y, self._yaw, self._stamp


# ==================== TCP 发帧器 ====================

class Sender:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(3.0)
        self.sock.connect((TCP_IP, TCP_PORT))
        self.sock.settimeout(None)
        self.seq = 0
        print(f"✅ 已连接下位机 {TCP_IP}:{TCP_PORT}")

    def send(self, channels, yaw=0, des_yaw=0):
        self.sock.sendall(build_frame(self.seq, channels, yaw, des_yaw))
        self.seq = (self.seq + 1) & 0xFFFF

    def stop(self):
        self.send(motion_channels(0, 0, 0), yaw=0, des_yaw=0)

    def close(self):
        try:
            self.stop()
        except Exception:
            pass
        try:
            self.sock.close()
        except Exception:
            pass


# ==================== PID 导航（参考 usc move_to_target）====================

def pid_turn_to(sender, localizer, target_yaw_deg, timeout=10.0):
    """原地转向到目标朝向（航向 PID 闭环）。"""
    start = time.time()
    last_print = 0.0
    while True:
        if time.time() - start > timeout:
            sender.stop()
            return False
        p = localizer.get_pose()
        if p[3] == 0:
            time.sleep(0.02)
            continue
        _, _, yaw, _ = p
        yaw_deg = math.degrees(yaw)
        err = norm_deg(target_yaw_deg - yaw_deg)
        if abs(err) <= TURN_TOL_DEG:
            sender.stop()
            return True
        # 调试：每 0.5 秒打印当前朝向/目标/误差，用于诊断原地旋转
        if time.time() - last_print > 0.5:
            last_print = time.time()
            print(f"  [调试] yaw={yaw_deg:.1f}° 目标={target_yaw_deg:.1f}° 误差={err:.1f}°")
        des_yaw_deg = yaw_deg + TURN_GAIN * err
        sender.send(motion_channels(0, 0, 0),
                     yaw=yaw_deg_to_i16(yaw_deg),
                     des_yaw=yaw_deg_to_i16(des_yaw_deg))
        time.sleep(1.0 / FRAME_HZ)


def pid_drive_to(sender, localizer, tx, ty, hold_yaw_deg, timeout=30.0):
    """位置保持式直行到目标点（usc 的位置闭环：偏差→车体系→比例控制）。"""
    start = time.time()
    while True:
        if time.time() - start > timeout:
            sender.stop()
            return False
        p = localizer.get_pose()
        if p[3] == 0:
            time.sleep(0.02)
            continue
        cx, cy, yaw, _ = p
        yaw_deg = math.degrees(yaw)
        dx = tx - cx
        dy = ty - cy
        dist = math.hypot(dx, dy)
        if dist < STOP_DISTANCE:
            sender.stop()
            return True
        # 世界偏差 → 车体系（参考 usc world_error_to_fixed_body）
        forward_err = math.cos(yaw) * dx + math.sin(yaw) * dy
        lateral_err = -math.sin(yaw) * dx + math.cos(yaw) * dy
        speed = min(PID_KP * dist, PID_MAX_SPEED)
        forward = speed * forward_err / dist if dist > 1e-6 else 0.0
        lateral = speed * lateral_err / dist if dist > 1e-6 else 0.0
        sender.send(motion_channels(lateral=lateral, forward=forward),
                     yaw=yaw_deg_to_i16(yaw_deg),
                     des_yaw=yaw_deg_to_i16(hold_yaw_deg))
        time.sleep(1.0 / FRAME_HZ)


def load_points(path):
    """读取 points.txt，解析 origin（起始）和 target（目标点）。"""
    origin = None
    targets = []
    try:
        with open(path) as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) < 4:
                    continue
                kind = parts[0]
                x, y, yaw = float(parts[1]), float(parts[2]), float(parts[3])
                if kind == "origin":
                    origin = (x, y, yaw)
                elif kind == "target":
                    targets.append((x, y, yaw))
    except FileNotFoundError:
        pass
    return origin, targets


def plan_path(plan_client, localizer, gx, gy, timeout=10.0):
    """用 Nav2 全局规划器规划一条绕障路径，返回路径点列表 [(x, y), ...]。失败返回 None。"""
    cx, cy, _, _ = localizer.get_pose()
    goal = ComputePathToPose.Goal()
    goal.start = PoseStamped()
    goal.start.header.frame_id = "map"
    goal.start.pose.position.x = float(cx)
    goal.start.pose.position.y = float(cy)
    goal.start.pose.orientation.w = 1.0
    goal.goal = PoseStamped()
    goal.goal.header.frame_id = "map"
    goal.goal.pose.position.x = float(gx)
    goal.goal.pose.position.y = float(gy)
    goal.goal.pose.orientation.w = 1.0

    future = plan_client.send_goal_async(goal)
    rclpy.spin_until_future_complete(localizer, future, timeout_sec=3.0)
    if not future.done():
        return None
    goal_handle = future.result()
    if goal_handle is None or not goal_handle.accepted:
        return None

    result_future = goal_handle.get_result_async()
    rclpy.spin_until_future_complete(localizer, result_future, timeout_sec=timeout)
    if not result_future.done():
        return None
    resp = result_future.result()
    if resp is None or resp.result is None:
        return None
    path = resp.result.path
    if path is None or not path.poses:
        return None
    return [(p.pose.position.x, p.pose.position.y) for p in path.poses]


def main():
    rclpy.init()
    localizer = Localizer()
    executor = SingleThreadedExecutor()
    executor.add_node(localizer)
    threading.Thread(target=executor.spin, daemon=True).start()

    # Nav2 规划器客户端
    plan_client = ActionClient(localizer, ComputePathToPose, PLAN_ACTION)

    sender = None
    try:
        # 等定位
        print(f"等待 {ROBOT_ODOM_TOPIC} ...")
        t0 = time.time()
        while time.time() - t0 < 30.0:
            if localizer.get_pose()[3] > 0:
                print("✅ 定位就绪")
                break
            time.sleep(0.1)
        else:
            print(f"❌ 30 秒没收到 {ROBOT_ODOM_TOPIC}，请确认雷达驱动 + Super-LIO 已启动")
            return

        # ③ 打印起始坐标 + 目标坐标
        origin, targets = load_points(POINTS_FILE)
        if origin is not None:
            print(f"起始坐标：({origin[0]:.3f}, {origin[1]:.3f}, 朝向 {origin[2]:.1f}°)")
        else:
            print("⚠️ 未找到起始点")
        if not targets:
            print(f"⚠️ 没有目标点（{POINTS_FILE} 为空），手动输入：")
            try:
                x = float(input("  目标 x："))
                y = float(input("  目标 y："))
                yaw = float(input("  目标朝向（度）："))
                targets = [(x, y, yaw)]
            except ValueError:
                return
        for i, (x, y, yaw_deg) in enumerate(targets, 1):
            print(f"目标坐标 #{i}：({x:.3f}, {y:.3f}, 朝向 {yaw_deg:.1f}°)")

        # ④ 确认是否开始导航
        resp = input("\n是否开始导航至目标点位? (y/n): ").strip().lower()
        if resp != "y":
            print("已取消导航")
            return

        # ⑤ 等 Nav2 规划器
        print(f"等待 Nav2 规划器 {PLAN_ACTION} ...")
        nav_available = plan_client.wait_for_server(timeout_sec=10.0)
        if not nav_available:
            print("⚠️ Nav2 未就绪，退回直线 PID 导航（无绕障）")
        else:
            print("✅ Nav2 规划器就绪")

        # ⑥ 连接下位机
        sender = Sender()
        sender.stop()

        print(f"\n开始依次到达 {len(targets)} 个目标点...")
        for i, (x, y, yaw_deg) in enumerate(targets, 1):
            print(f"\n>> 目标 #{i}：({x:.3f}, {y:.3f}, {yaw_deg:.1f}°)")

            # ① 用 Nav2 规划绕障路径
            waypoints = None
            if nav_available:
                waypoints = plan_path(plan_client, localizer, x, y)
                if waypoints and len(waypoints) > 1:
                    print(f"  Nav2 规划出 {len(waypoints)} 个路径点，沿路径行走")
                else:
                    print("  规划失败，退回直线 PID")
                    waypoints = None

            # ② 沿路径点 PID 行走
            if waypoints:
                # 逐个路径点走（跳过离当前太近的点）
                for (wx, wy) in waypoints[1:]:
                    cx, cy, _, _ = localizer.get_pose()
                    if math.hypot(wx - cx, wy - cy) < 0.1:
                        continue
                    approach_yaw = math.degrees(math.atan2(wy - cy, wx - cx))
                    if not pid_turn_to(sender, localizer, approach_yaw):
                        break
                    if not pid_drive_to(sender, localizer, wx, wy, approach_yaw):
                        break
                # 到位后对准目标朝向
                pid_turn_to(sender, localizer, yaw_deg)
                print(f">> 目标 #{i} 到达 ✅")
            else:
                # 无 Nav2，直线 PID（原逻辑）
                cx, cy, _, _ = localizer.get_pose()
                approach_yaw = math.degrees(math.atan2(y - cy, x - cx))
                if pid_turn_to(sender, localizer, approach_yaw):
                    if pid_drive_to(sender, localizer, x, y, approach_yaw):
                        if abs(norm_deg(yaw_deg - approach_yaw)) > TURN_TOL_DEG:
                            pid_turn_to(sender, localizer, yaw_deg)
                        print(f">> 目标 #{i} 到达 ✅")
                    else:
                        print(f">> 目标 #{i} PID 失败 ❌")
                else:
                    print(f">> 目标 #{i} 转向失败 ❌")

        print("\n导航结束")

    except KeyboardInterrupt:
        print("\n🛑 Ctrl+C 急停")
    except Exception as e:
        print(f"❌ 出错：{e}")
    finally:
        if sender is not None:
            sender.close()
        executor.shutdown()
        rclpy.shutdown()
        print("已安全退出")


if __name__ == "__main__":
    main()
