#!/usr/bin/env python3
"""Read-only ROS diagnostics. Keep nav.launch.py running and the robot stationary."""

import argparse
from collections import defaultdict, deque
import hashlib
import math
from pathlib import Path
import sys
import time

import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from rclpy.time import Time
from rclpy.utilities import remove_ros_args
from lifecycle_msgs.srv import GetState
from nav_msgs.msg import OccupancyGrid, Odometry
from rcl_interfaces.srv import GetParameters
from rosidl_runtime_py.convert import message_to_ordereddict
from sensor_msgs.msg import Imu, PointCloud2
from tf2_msgs.msg import TFMessage
from tf2_ros import Buffer, TransformListener

HERE = Path(__file__).resolve().parent


def rpy(q):
    values = (q.x, q.y, q.z, q.w)
    if not all(math.isfinite(v) for v in values):
        raise ValueError("四元数含 NaN/Inf")
    norm = math.sqrt(sum(v * v for v in values))
    if norm < 1e-9:
        raise ValueError("四元数为零")
    x, y, z, w = (v / norm for v in values)
    return (
        math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y)),
        math.asin(max(-1.0, min(1.0, 2 * (w * y - z * x)))),
        math.atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z)),
    )


def rotate(q, xyz):
    rpy(q)  # Validate before using a normalized rotation.
    norm = math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w)
    ux, uy, uz, w = (v / norm for v in (q.x, q.y, q.z, q.w))
    x, y, z = xyz
    tx, ty, tz = 2*(uy*z-uz*y), 2*(uz*x-ux*z), 2*(ux*y-uy*x)
    return (x+w*tx+uy*tz-uz*ty, y+w*ty+uz*tx-ux*tz,
            z+w*tz+ux*ty-uy*tx)


def grid_cell(grid, x, y):
    """Coordinates are in grid.header.frame_id; rows start at map origin."""
    info = grid.info
    if info.resolution <= 0 or len(grid.data) != info.width * info.height:
        raise ValueError("地图尺寸或数据长度无效")
    roll, pitch, yaw = rpy(info.origin.orientation)
    if abs(roll) > 1e-6 or abs(pitch) > 1e-6:
        raise ValueError("二维地图原点含 roll/pitch，不能按水平栅格检查")
    dx, dy = x-info.origin.position.x, y-info.origin.position.y
    col = math.floor((math.cos(yaw)*dx + math.sin(yaw)*dy) / info.resolution)
    row = math.floor((-math.sin(yaw)*dx + math.cos(yaw)*dy) / info.resolution)
    if not (0 <= col < info.width and 0 <= row < info.height):
        return col, row, None
    return col, row, int(grid.data[row * info.width + col])


class Diagnostics(Node):
    def __init__(self):
        super().__init__("mid360_readonly_diagnostics")
        self.latest = {}
        self.counts = defaultdict(int)
        self.arrivals = {}
        self.poses = defaultdict(lambda: deque(maxlen=6000))
        self.edges = {}
        self.parents = defaultdict(set)
        self.tf_publishers = defaultdict(set)
        self.buffer = Buffer()
        self.listener = TransformListener(self.buffer, self)
        self.subscriptions_keep = []
        sensor = QoSProfile(depth=5, reliability=ReliabilityPolicy.BEST_EFFORT)
        retained = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL,
                              reliability=ReliabilityPolicy.BEST_EFFORT)
        for topic, kind in (("/livox/imu", Imu), ("/lio/robo/odom", Odometry),
                            ("/lio/odom", Odometry), ("/lio/cloud_world", PointCloud2)):
            self.subscribe(topic, kind, sensor)
        for topic in ("/map", "/global_costmap/costmap"):
            self.subscribe(topic, OccupancyGrid, retained)
        self.notes = []
        try:
            from livox_ros_driver2.msg import CustomMsg
            self.subscribe("/livox/lidar", CustomMsg, sensor)
        except ImportError:
            self.notes.append("未加载 Livox 消息类型；无法采样 /livox/lidar，仍可检查发布者及 LIO。")
        self.subscriptions_keep.append(self.create_subscription(
            TFMessage, "/tf", self.tf_callback, sensor))
        self.subscriptions_keep.append(self.create_subscription(
            TFMessage, "/tf_static", self.static_tf_callback, retained))
        self.param_names = ["lio.relocation.init_pose", "lio.extrinsic.odom_robo",
                            "lio.extrinsic.lidar_imu", "lio.map.save_map",
                            "lio.relocation.update_map", "lio.sensor.blind"]
        self.params_client = self.create_client(GetParameters, "/relocation_node/get_parameters")
        self.state_client = self.create_client(GetState, "/planner_server/get_state")
        self.params_future = self.state_future = None

    def subscribe(self, topic, kind, qos):
        self.subscriptions_keep.append(self.create_subscription(
            kind, topic, lambda msg: self.receive(topic, msg), qos))

    def receive(self, topic, msg):
        now = time.monotonic()
        self.latest[topic] = msg
        self.counts[topic] += 1
        first = self.arrivals.get(topic, (now, now))[0]
        self.arrivals[topic] = first, now
        if isinstance(msg, Odometry):
            p = msg.pose.pose
            self.poses[topic].append((p.position.x, p.position.y,
                                       p.orientation, msg.header.frame_id))

    def static_tf_callback(self, msg, info):
        self.record_tf(msg, info, True)

    def tf_callback(self, msg, info):
        self.record_tf(msg, info, False)

    def record_tf(self, msg, info, static):
        gid = bytes(info.publisher_gid).hex()
        for transform in msg.transforms:
            parent = transform.header.frame_id.lstrip("/")
            child = transform.child_frame_id.lstrip("/")
            self.parents[child].add(parent)
            self.edges[(parent, child)] = transform, static
            self.tf_publishers[(parent, child)].add(gid)

    def query_services(self):
        if self.params_future is None and self.params_client.service_is_ready():
            request = GetParameters.Request(names=self.param_names)
            self.params_future = self.params_client.call_async(request)
        if self.state_future is None and self.state_client.service_is_ready():
            self.state_future = self.state_client.call_async(GetState.Request())

    def age(self, stamp):
        return (self.get_clock().now().nanoseconds -
                (stamp.sec * 1000000000 + stamp.nanosec)) / 1e9

    def point_in_frame(self, xyz, source, target, stamp):
        if source == target:
            return xyz
        transform = self.buffer.lookup_transform(target, source, Time.from_msg(stamp)).transform
        x, y, z = rotate(transform.rotation, xyz)
        t = transform.translation
        return x+t.x, y+t.y, z+t.z

    def report(self):
        print("\n=== Mid-360 只读检测：未连接 TCP，未发运动、重定位或清图命令 ===")
        print("节点：" + ", ".join(sorted(self.get_node_names())))
        for note in self.notes:
            print("提示：" + note)
        print("\n[数据流：频率为本次订阅接收频率]")
        topics = ("/livox/lidar", "/livox/imu", "/lio/robo/odom", "/lio/odom",
                  "/lio/cloud_world", "/map", "/global_costmap/costmap")
        for topic in topics:
            endpoints = self.get_publishers_info_by_topic(topic)
            names = [e.node_namespace.rstrip("/") + "/" + e.node_name for e in endpoints]
            print(f"{topic}: 发布者={names}", end="")
            msg = self.latest.get(topic)
            if msg is None:
                print("；采样期间未收到数据")
                continue
            first, last = self.arrivals[topic]
            rate = (self.counts[topic]-1)/(last-first) if last > first else 0.0
            print(f"；收到={self.counts[topic]}，{rate:.1f} Hz", end="")
            if hasattr(msg, "header"):
                age = self.age(msg.header.stamp)
                print(f"；frame={msg.header.frame_id}，源时间年龄={age:.3f}s", end="")
                if topic.startswith(("/lio/", "/livox/")) and (age > .5 or age < -.05):
                    print(" [警告：过期或时钟异常]", end="")
            if isinstance(msg, PointCloud2):
                print(f"；点数={msg.width*msg.height}", end="")
            print()
            if len(endpoints) > 1 and topic not in ("/livox/imu",):
                print("  警告：多个发布者，检查是否同时运行了不同定位/导航实例。")

        print("\n[TF 实际收到的边]")
        for (parent, child), (msg, static) in sorted(self.edges.items()):
            t = msg.transform.translation
            try:
                angles = tuple(round(math.degrees(v), 2) for v in rpy(msg.transform.rotation))
            except ValueError as exc:
                angles = str(exc)
            timing = "静态" if static else f"动态 age={self.age(msg.header.stamp):.3f}s"
            print(f"{parent} -> {child}: {timing}，xyz=({t.x:.3f},{t.y:.3f},{t.z:.3f}) "
                  f"RPY度={angles}，发布者数={len(self.tf_publishers[(parent, child)])}")
            if len(self.tf_publishers[(parent, child)]) > 1:
                print("  警告：同一 TF 边存在多个发布者，需检查重复节点。")
        for child, parents in self.parents.items():
            if len(parents) > 1:
                print(f"警告：TF 子帧 {child} 存在不同父帧 {sorted(parents)}")
        for parent, child in (("map", "world"), ("world", "imu"), ("imu", "base_link")):
            if (parent, child) not in self.edges:
                print(f"警告：采样期间未收到必需边 {parent} -> {child}")
        for child in ("world", "imu", "base_link"):
            try:
                tf = self.buffer.lookup_transform("map", child, Time())
                t = tf.transform.translation
                print(f"可查询 map -> {child}: xyz=({t.x:.3f},{t.y:.3f},{t.z:.3f})")
                if child == "world":
                    angles = rpy(tf.transform.rotation)
                    if max(abs(t.x), abs(t.y), abs(t.z), *(abs(v) for v in angles)) > 1e-6:
                        print("警告：map->world 不是恒等变换，当前导航脚本直接使用 world XY 作为 map XY，需修正。")
            except Exception as exc:
                print(f"不可查询 map -> {child}: {exc}")

        print("\n[定位：仅在车保持静止时，采样变化才代表漂移]")
        for topic, samples in self.poses.items():
            p = self.latest[topic].pose.pose
            try:
                roll, pitch, yaw = (math.degrees(v) for v in rpy(p.orientation))
                distance = math.hypot(samples[-1][0]-samples[0][0], samples[-1][1]-samples[0][1])
                spread = max(math.hypot(s[0]-samples[0][0], s[1]-samples[0][1]) for s in samples)
                print(f"{topic}: xyz=({p.position.x:.3f},{p.position.y:.3f},{p.position.z:.3f}) "
                      f"RPY=({roll:.2f},{pitch:.2f},{yaw:.2f})度；"
                      f"首末位移={distance:.3f}m，距首帧最大变化={spread:.3f}m")
                if len({s[3] for s in samples}) > 1:
                    print("  警告：采样期间定位 frame_id 改变。")
                if abs(roll) > 15 or abs(pitch) > 15:
                    print("  提示：较大倾角需结合雷达安装角及建图坐标检查，不能仅凭倾角判定匹配失败。")
            except ValueError as exc:
                print(f"{topic}: 无效姿态 {exc}")

        print("\n[实时二维地图与代价图：检测中心栅格，不证明整个 footprint 可通过]")
        robo = self.latest.get("/lio/robo/odom")
        targets = []
        points_file = HERE / "points.txt"
        if points_file.exists():
            for line in points_file.read_text().splitlines():
                fields = line.split()
                if len(fields) >= 4 and fields[0] == "target":
                    targets.append((float(fields[1]), float(fields[2])))
        for topic in ("/map", "/global_costmap/costmap"):
            grid = self.latest.get(topic)
            if grid is None:
                print(f"{topic}: 缺少数据，不能判断边界/障碍")
                continue
            info = grid.info
            print(f"{topic}: frame={grid.header.frame_id}，{info.width}x{info.height}，"
                  f"分辨率={info.resolution}，原点=({info.origin.position.x:.3f},{info.origin.position.y:.3f})")
            try:
                roll, pitch, yaw = rpy(info.origin.orientation)
                if max(abs(roll), abs(pitch), abs(yaw)) < 1e-6:
                    print(f"  范围 x=[{info.origin.position.x:.3f},{info.origin.position.x+info.width*info.resolution:.3f}) "
                          f"y=[{info.origin.position.y:.3f},{info.origin.position.y+info.height*info.resolution:.3f})")
                checks = [(f"目标#{i}", (x, y, 0.0), "map", self.get_clock().now().to_msg())
                          for i, (x, y) in enumerate(targets, 1)]
                if robo is not None:
                    p = robo.pose.pose.position
                    checks.insert(0, ("实时起点", (p.x, p.y, p.z), robo.header.frame_id, robo.header.stamp))
                for label, xyz, frame, stamp in checks:
                    try:
                        x, y, _ = self.point_in_frame(xyz, frame, grid.header.frame_id, stamp)
                        col, row, value = grid_cell(grid, x, y)
                        if value is None:
                            state = "地图外：当前栅格图无法从这里规划"
                        elif value == -1:
                            state = "未知区域（allow_unknown=false 时不能通过）"
                        elif topic == "/map" and value >= 65:
                            state = "静态占用区域"
                        elif topic != "/map" and value >= 99:
                            state = "致命/内切膨胀障碍区域"
                        else:
                            state = "中心栅格未被判为致命障碍；仍需检查 footprint 和路径连通性"
                        print(f"  {label}: ({x:.3f},{y:.3f})，格=({col},{row})，值={value}；{state}")
                    except Exception as exc:
                        print(f"  {label}: 无法转换或检查 {exc}")
            except ValueError as exc:
                print(f"  无效地图：{exc}")

        print("\n[在线配置与规划器状态]")
        for label, future in (("重定位参数", self.params_future), ("规划器状态", self.state_future)):
            if future is None or not future.done():
                print(f"{label}: 查询未完成/服务不可用")
                continue
            try:
                result = future.result()
                if label == "规划器状态":
                    print(f"{label}: {result.current_state.label}")
                else:
                    for name, value in zip(self.param_names, result.values):
                        print(f"{name}: {dict(message_to_ordereddict(value))}")
            except Exception as exc:
                print(f"{label}: {exc}")
        print("\n[本机文件指纹：用于核对归档，不同类型地图哈希不同不代表坐标不一致]")
        paths = [HERE / "map2d.yaml", HERE / "map2d.pgm", points_file,
                 HERE / "map3d.pcd", HERE.parent / "lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd"]
        for path in paths:
            if path.is_file():
                digest = hashlib.sha256()
                with path.open("rb") as stream:
                    for block in iter(lambda: stream.read(1024*1024), b""):
                        digest.update(block)
                print(f"{path}: 字节={path.stat().st_size} sha256={digest.hexdigest()}")
            else:
                print(f"{path}: 不存在")
        print("\n判读：TF 连通和 ICP 收敛均不能证明实际位置正确；地图外也不能单独证明 ICP 误匹配。")
        print("若起点在地图外：先核对真实位置、PCD/二维图是否同次建图及二维切片范围。")
        print("若静止时定位明显变化：核对雷达/IMU 时间戳、外参、现场特征及匹配日志。")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--seconds", type=float, default=15.0)
    args = parser.parse_args(remove_ros_args()[1:])
    if not math.isfinite(args.seconds) or not 1 <= args.seconds <= 120:
        parser.error("--seconds 应在 1 到 120 之间")
    rclpy.init()
    node = Diagnostics()
    try:
        print(f"保持 launch 运行、车静止，采样 {args.seconds:g}s；本脚本不会控制底盘。", flush=True)
        deadline = time.monotonic() + args.seconds
        while rclpy.ok() and time.monotonic() < deadline:
            node.query_services()
            rclpy.spin_once(node, timeout_sec=0.1)
        node.report()
        return 0
    except KeyboardInterrupt:
        return 130
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == "__main__":
    sys.exit(main())
