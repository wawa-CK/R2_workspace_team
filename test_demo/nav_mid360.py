#!/usr/bin/env python3
"""
Mid360 导航脚本 —— Nav2 绕障规划 + PID 导航。

用法（nav.launch.py 启动驱动、重定位和规划器；本脚本另开终端运行）：
    source /opt/ros/humble/setup.bash
    source ~/r2_ws/lidar_ws/install/setup.bash
    cd ~/r2_ws/test_demo
    ros2 launch "$(pwd)/nav.launch.py"
    python3 nav_mid360.py

注意：雷达需按"先启动、后上电"顺序（先跑本命令，再给雷达上电），否则驱动可能握不上手。

交互流程：
    1. Nav2 已由 launch 加载地图 + 绕障规划器 + TF 桥
    2. 打印起始坐标、目标点坐标
    3. 询问"是否开始导航至目标点位"，按 y 确认后开始
    4. 用 Nav2 规划绕障路径，全向底盘保持起始朝向跟随路径，最后转向
    5. 只有实时位置和朝向都通过复核，才报告到达；任一步失败即停车

    python3 nav_mid360.py --check-only 只检查定位和规划，不连接下位机。

PID 控制（参考 usc move_to_target）：
    每周期读当前位置，算偏差 → 转到车体系 → 比例控制 → ch0/ch2 速度
"""

import argparse
import bisect
import math
from pathlib import Path
import socket
import struct
import threading
import time
import sys

import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from rclpy.action import ActionClient
from rclpy.utilities import remove_ros_args
from rclpy.qos import qos_profile_sensor_data
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import ComputePathToPose
from action_msgs.msg import GoalStatus

# ==================== 网络 / 话题 ====================
TCP_IP = "192.168.2.199"
TCP_PORT = 5000
ROBOT_ODOM_TOPIC = "/lio/robo/odom"
POINTS_FILE = Path(__file__).resolve().parent / "points.txt"
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
PID_MAX_SPEED = 270      # 与手动前后通道速度一致；速度参数允许的最大值
DEFAULT_FORWARD_SPEED = PID_MAX_SPEED  # 默认前后速度（ch2）
DEFAULT_LATERAL_SPEED = PID_MAX_SPEED  # 默认横移速度（ch0）
PATH_LOOKAHEAD = 0.35    # 连续路径跟踪前瞻距离（米）
STOP_DISTANCE = 0.05     # 到达路径点的容差（米）
FINAL_POSITION_TOLERANCE = 0.03  # 最终位置误差要求（米）
FINAL_CORRECTION_ATTEMPTS = 3  # 转向漂移后的位置/朝向联合回正次数
FINAL_CORRECTION_MAX_DISTANCE = 0.30  # 停车后允许低速回正的最大偏移（米）
FINAL_CORRECTION_SPEED = 80  # 最终对位的通道上限
TURN_TOL_DEG = 2.0       # 转向到位容差（度）
TURN_GAIN = 1.0          # 航向误差比例增益，最终受 MAX_YAW_COMMAND_DEG 限幅
MAX_YAW_COMMAND_DEG = 10.0  # 每帧航向误差上限；按现有下位机 Kp 约为 0.47rad/s
TURN_COMMAND_SIGN = 1     # 实测正航向命令让 ROS yaw 减小时才改为 -1
POSE_TIMEOUT = 0.5        # 定位的源时间年龄+接收后经过时间上限，不仅是回调间隔
FUTURE_STAMP_TOLERANCE = 0.05  # 源时间超前 ROS 时钟超过 50ms 时拒绝使用
WAYPOINT_TOLERANCE = 0.05 # 路径中间点容差
MAX_DISTANCE_REGRESSION = 0.10  # 距当前路径点比本段最佳距离增大超过 10cm，只报警
DEFAULT_BODY_YAW_OFFSET_DEG = 180.0  # 直线实车验证：0° 时远离目标，平移换算需反向
LATERAL_COMMAND_SIGN = -1  # 实车验证：ch0 正值向错误侧横移，需翻转横移通道
INITIAL_POSE_SETTLE_SEC = 2.0  # 首帧定位后留出稳定时间，期间不规划、不连接底盘


class NavigationError(RuntimeError):
    """定位、规划或控制失败；调用方必须停止当前任务。"""


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
    if not math.isfinite(d):
        raise NavigationError("航向不是有限数值")
    return (d + 180.0) % 360.0 - 180.0


def yaw_deg_to_i16(d):
    if not math.isfinite(d):
        raise NavigationError("航向不是有限数值")
    value = int(round(d * 100.0))
    if not -32768 <= value <= 32767:
        raise NavigationError(f"航向超出协议 int16 范围：{d}")
    return value


def heading_command(current_deg, target_deg):
    """保留真实 yaw，发送限幅后的最短角误差，避免跨 ±180° 反转。"""
    current_deg = norm_deg(current_deg)
    error = norm_deg(target_deg - current_deg)
    step = TURN_COMMAND_SIGN * max(-MAX_YAW_COMMAND_DEG,
                                   min(MAX_YAW_COMMAND_DEG, TURN_GAIN * error))
    yaw = yaw_deg_to_i16(current_deg)
    # 不能单独归一化目标，否则简单相减会把 2° 变成 358°。
    desired = yaw_deg_to_i16(current_deg + step)
    # 现有协议 des_yaw=0 表示关闭航向 PID；目标 0° 用 0.01° 表示。
    return yaw, desired if desired != 0 else 1


def fresh_pose(localizer):
    pose = localizer.get_pose()
    if not all(math.isfinite(v) for v in pose):
        raise NavigationError("定位包含 NaN/Inf")
    age = time.monotonic() - pose[3]
    if pose[3] <= 0.0 or age < 0.0 or age > POSE_TIMEOUT:
        raise NavigationError(f"定位未更新（{age:.2f}s），停止导航；检查 /lio/robo/odom")
    return pose


# ==================== 定位节点 ====================

class Localizer(Node):
    def __init__(self):
        super().__init__("mid360_nav_localizer")
        self._lock = threading.Lock()
        self._x = 0.0
        self._y = 0.0
        self._yaw = 0.0
        self._stamp = 0.0
        self._source_stamp = None
        # 控制只需要最新状态，减少回放队列中的历史定位。
        self.create_subscription(Odometry, ROBOT_ODOM_TOPIC, self._cb, 1)

    def _cb(self, msg):
        p = msg.pose.pose
        q = p.orientation
        values = (p.position.x, p.position.y, q.x, q.y, q.z, q.w)
        if msg.header.frame_id not in ("world", "map") or not all(
                math.isfinite(v) for v in values):
            self.get_logger().error("定位坐标系不是 world/map 或包含非法数值")
            return
        norm = math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w)
        if norm < 1e-6:
            self.get_logger().error("定位四元数无效")
            return
        source_stamp = msg.header.stamp.sec * 1000000000 + msg.header.stamp.nanosec
        source_age = (self.get_clock().now().nanoseconds - source_stamp) / 1e9
        if source_stamp <= 0 or source_age > POSE_TIMEOUT or source_age < -FUTURE_STAMP_TOLERANCE:
            self.get_logger().warning(
                f"拒绝过期或时钟异常的定位：消息年龄={source_age:.3f}s；检查时间戳与定位处理延迟",
                throttle_duration_sec=2.0)
            return
        with self._lock:
            if self._source_stamp is not None and source_stamp <= self._source_stamp:
                return  # 重复/乱序旧消息不能刷新定位看门狗
            self._source_stamp = source_stamp
            self._x = float(p.position.x)
            self._y = float(p.position.y)
            self._yaw = quat_to_yaw(q.x/norm, q.y/norm, q.z/norm, q.w/norm)
            # 把测量时刻映射到单调时钟；排队 0.4s 的消息不能再获得完整 0.5s 有效期。
            self._stamp = time.monotonic() - max(0.0, source_age)

    def get_pose(self):
        with self._lock:
            return self._x, self._y, self._yaw, self._stamp


def summarize_stationary_samples(samples):
    """samples: (接收单调时间, 消息年龄, x, y, yaw弧度)，仅作静止诊断。"""
    if not samples:
        return None
    first = samples[0]
    elapsed = samples[-1][0] - first[0]
    ages = [row[1] for row in samples]
    ordered_ages = sorted(ages)
    max_age_index = max(range(len(samples)), key=lambda i: samples[i][1])
    return {
        "count": len(samples),
        "rate": (len(samples)-1) / elapsed if elapsed > 0 else 0.0,
        "age_mean": sum(ages) / len(ages),
        "age_min": min(ages), "age_max": max(ages),
        "age_p95": ordered_ages[math.ceil(0.95 * len(ordered_ages))-1],
        "age_over_limit_count": sum(age > POSE_TIMEOUT for age in ages),
        "age_max_at": samples[max_age_index][0]-first[0],
        "drift_max": max(math.hypot(row[2]-first[2], row[3]-first[3]) for row in samples),
        "x_span": max(row[2] for row in samples)-min(row[2] for row in samples),
        "y_span": max(row[3] for row in samples)-min(row[3] for row in samples),
        "yaw_span_from_start": max(abs(norm_deg(math.degrees(row[4]-first[4]))) for row in samples),
    }


def check_localization(duration=10.0, warmup_duration=3.0):
    """只订阅两个定位话题：不读目标，不创建规划客户端或 TCP Sender。"""
    rclpy.init()
    node = Node("mid360_stationary_check")
    topics = (ROBOT_ODOM_TOPIC, "/lio/odom")
    samples = {topic: [] for topic in topics}
    frames = {topic: set() for topic in topics}
    invalid = {topic: 0 for topic in topics}
    reversed_stamps = {topic: 0 for topic in topics}
    last_stamps = {}
    subscriptions = []

    def receive(topic, msg):
        p, q = msg.pose.pose.position, msg.pose.pose.orientation
        vals = (p.x, p.y, q.x, q.y, q.z, q.w)
        if not all(math.isfinite(v) for v in vals):
            invalid[topic] += 1
            return
        length = math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w)
        if length < 1e-6:
            invalid[topic] += 1
            return
        stamp = msg.header.stamp.sec * 1000000000 + msg.header.stamp.nanosec
        if topic in last_stamps and stamp <= last_stamps[topic]:
            reversed_stamps[topic] += 1
        last_stamps[topic] = stamp
        age = (node.get_clock().now().nanoseconds - stamp) / 1e9
        yaw = quat_to_yaw(q.x/length, q.y/length, q.z/length, q.w/length)
        samples[topic].append((time.monotonic(), age, float(p.x), float(p.y), yaw))
        frames[topic].add(msg.header.frame_id)

    try:
        for topic in topics:
            subscriptions.append(node.create_subscription(
                Odometry, topic, lambda msg, t=topic: receive(t, msg), qos_profile_sensor_data))
        print(f"静止定位检查：请保持车不动，先预热 {warmup_duration:g} 秒，"
              f"再统计 {duration:g} 秒。不会连接底盘。")
        print("/lio/robo/odom：IMU 预测位置；/lio/odom：雷达更新后的状态位置。")
        if warmup_duration > 0:
            warmup_start = time.monotonic()
            while rclpy.ok() and time.monotonic()-warmup_start < warmup_duration:
                rclpy.spin_once(node, timeout_sec=0.1)
            print("启动阶段统计（单独保留，不混入后续稳定采样）：")
            for topic in topics:
                summary = summarize_stationary_samples(samples[topic])
                if summary is not None:
                    print(f"  {topic}: 样本={summary['count']}，最大消息年龄={summary['age_max']:.4f}s，"
                          f"超过{POSE_TIMEOUT:.1f}s={summary['age_over_limit_count']}帧")
                else:
                    print(f"  {topic}: 尚未收到有效数据")
                samples[topic].clear()
                frames[topic].clear()
                invalid[topic] = reversed_stamps[topic] = 0
            print(f"开始后续 {duration:g} 秒静止采样。")
        start = time.monotonic()
        next_print = start + 1.0
        while rclpy.ok() and time.monotonic()-start < duration:
            rclpy.spin_once(node, timeout_sec=0.1)
            now = time.monotonic()
            if now >= next_print:
                next_print = now + 1.0
                for topic in topics:
                    if samples[topic]:
                        row, first = samples[topic][-1], samples[topic][0]
                        shift = math.hypot(row[2]-first[2], row[3]-first[3])
                        print(f"{topic}: x={row[2]:.3f} y={row[3]:.3f} "
                              f"yaw={math.degrees(row[4]):.1f}° 相对首帧={shift:.3f}m "
                              f"消息年龄={row[1]:.3f}s 距上次接收={now-row[0]:.3f}s")
                    else:
                        print(f"{topic}: 尚未收到数据")
        print("\n静止检查汇总（位置变化只在车确实静止时解释为估计变化）：")
        for topic in topics:
            summary = summarize_stationary_samples(samples[topic])
            print(f"{topic}: 发布者={node.count_publishers(topic)}，坐标系={sorted(frames[topic])}")
            if summary is None:
                print("  未收到有效数据；无法评估该定位输出。")
                continue
            gap = time.monotonic()-samples[topic][-1][0]
            print(f"  样本={summary['count']} 观测频率={summary['rate']:.1f}Hz "
                  f"末帧接收距今={gap:.3f}s")
            print(f"  消息年龄：平均={summary['age_mean']:.4f}s "
                  f"最小={summary['age_min']:.4f}s 最大={summary['age_max']:.4f}s")
            print(f"  P95={summary['age_p95']:.4f}s，超过{POSE_TIMEOUT:.1f}s="
                  f"{summary['age_over_limit_count']}帧，最大年龄出现在该话题首帧后"
                  f"{summary['age_max_at']:.2f}s")
            print(f"  相对首帧最大平移={summary['drift_max']:.4f}m，"
                  f"X范围={summary['x_span']:.4f}m，Y范围={summary['y_span']:.4f}m，"
                  f"最大朝向变化={summary['yaw_span_from_start']:.2f}°")
            print(f"  无效位姿={invalid[topic]}，重复/倒序时间戳={reversed_stamps[topic]}")
        print("消息年龄很小不代表位置准确；两话题各自对比首帧，不假定传感器与车体原点重合。")
        print("此检查未验证车体方向、雷达匹配质量或导航安全性。")
        return 0 if all(samples[topic] for topic in topics) else 1
    except KeyboardInterrupt:
        print("静止检查已中止，未连接底盘。")
        return 130
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


# ==================== TCP 发帧器 ====================

class Sender:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(3.0)
        self.sock.connect((TCP_IP, TCP_PORT))
        self.sock.settimeout(0.5)  # 网络故障不能让控制线程永久卡在 sendall
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

def pid_turn_to(sender, localizer, target_yaw_deg, timeout=15.0):
    """原地转向到目标朝向（航向 PID 闭环）。"""
    start = time.monotonic()
    last_print = 0.0
    while True:
        if time.monotonic() - start > timeout:
            sender.stop()
            print("  ❌ 转向超时；检查 yaw 是否持续更新、方向是否正确")
            return False
        try:
            p = fresh_pose(localizer)
        except NavigationError:
            sender.stop()
            raise
        _, _, yaw, _ = p
        yaw_deg = math.degrees(yaw)
        err = norm_deg(target_yaw_deg - yaw_deg)
        if abs(err) <= TURN_TOL_DEG:
            sender.stop()
            return True
        # 调试：每 0.5 秒打印当前朝向/目标/误差，用于诊断原地旋转
        if time.monotonic() - last_print > 0.5:
            last_print = time.monotonic()
            print(f"  [调试] yaw={yaw_deg:.1f}° 目标={target_yaw_deg:.1f}° 误差={err:.1f}°")
        yaw_cmd, des_cmd = heading_command(yaw_deg, target_yaw_deg)
        sender.send(motion_channels(0, 0, 0),
                     yaw=yaw_cmd, des_yaw=des_cmd)
        time.sleep(1.0 / FRAME_HZ)


def world_error_to_body(dx, dy, odom_yaw, body_yaw_offset_deg=0.0):
    """定位 yaw 加车体安装偏角后，转换为底盘前向/横向误差。

    偏角仅用于平移通道分解；点位与航向 PID 的两端仍使用原始定位 yaw，
    因此不修改已有地图、points.txt，也不把目标朝向额外旋转一次。
    """
    body_yaw = odom_yaw + math.radians(body_yaw_offset_deg)
    return (math.cos(body_yaw) * dx + math.sin(body_yaw) * dy,
            -math.sin(body_yaw) * dx + math.cos(body_yaw) * dy)


def print_direction_preview(waypoints, localizer, body_yaw_offset_deg,
                            goal=None, lookahead_distance=0.5):
    cx, cy, yaw, _ = fresh_pose(localizer)
    preview = None
    for wx, wy in waypoints:
        if math.hypot(wx - cx, wy - cy) >= lookahead_distance:
            preview = (wx, wy)
            break
    if preview is None:
        for wx, wy in reversed(waypoints):
            if math.hypot(wx - cx, wy - cy) > WAYPOINT_TOLERANCE:
                preview = (wx, wy)
                break
    if preview is not None:
        wx, wy = preview
        forward, lateral = world_error_to_body(
            wx - cx, wy - cy, yaw, body_yaw_offset_deg)
        direction = "前进(w)" if forward > 1e-6 else "后退(s)" if forward < -1e-6 else "无前后分量"
        print(f"  路径前瞻方向（约 {math.hypot(wx-cx, wy-cy):.2f}m）：{direction}；"
              f"前向误差={forward:+.3f}m，"
              f"横向误差={lateral:+.3f}m（对应 ch0 正负）")
    else:
        print("  路径点均在当前位置容差内，无平移方向可预览。")
    if goal is not None:
        gx, gy = goal
        forward, lateral = world_error_to_body(
            gx - cx, gy - cy, yaw, body_yaw_offset_deg)
        print(f"  最终目标相对车体：前向={forward:+.3f}m，横向={lateral:+.3f}m")


def pid_drive_to(sender, localizer, tx, ty, hold_yaw_deg, timeout=30.0,
                 tolerance=STOP_DISTANCE, *, body_yaw_offset_deg=0.0,
                 max_speed=DEFAULT_FORWARD_SPEED,
                 max_lateral_speed=DEFAULT_LATERAL_SPEED):
    """位置保持式直行到目标点（usc 的位置闭环：偏差→车体系→比例控制）。"""
    start = time.monotonic()
    best_distance = math.inf
    last_print = -math.inf
    regression_warned = False
    while True:
        if time.monotonic() - start > timeout:
            sender.stop()
            print(f"  ❌ 行走超时：目标 ({tx:.3f}, {ty:.3f})")
            return False
        try:
            p = fresh_pose(localizer)
        except NavigationError:
            sender.stop()
            raise
        cx, cy, yaw, _ = p
        yaw_deg = math.degrees(yaw)
        dx = tx - cx
        dy = ty - cy
        dist = math.hypot(dx, dy)
        if dist <= tolerance:
            sender.stop()
            return True
        # 对当前路径点检查，不能用最终目标距离，否则正常绕行也可能触发。
        best_distance = min(best_distance, dist)
        if dist - best_distance > MAX_DISTANCE_REGRESSION and not regression_warned:
            regression_warned = True
            print(f"  ⚠️ 正在远离当前路径点：当前距离={dist:.3f}m，"
                  f"本段最小距离={best_distance:.3f}m；继续运行，未发送停车指令")
        forward_err, lateral_err = world_error_to_body(
            dx, dy, yaw, body_yaw_offset_deg)
        speed = min(PID_KP * dist, max_speed)
        forward = speed * forward_err / dist if dist > 1e-6 else 0.0
        if dist > 1e-6:
            lateral_scale = max_lateral_speed / max_speed
            lateral = LATERAL_COMMAND_SIGN * max(
                -max_lateral_speed,
                min(max_lateral_speed, speed * lateral_err / dist * lateral_scale))
        else:
            lateral = 0.0
        if time.monotonic() - last_print >= 1.0:
            last_print = time.monotonic()
            body_yaw_deg = norm_deg(yaw_deg + body_yaw_offset_deg)
            print(f"  路径跟踪：距离={dist:.3f}m 定位yaw={yaw_deg:.1f}° "
                  f"车体yaw={body_yaw_deg:.1f}° ch2={int(forward):+d} "
                  f"ch0={int(lateral):+d}（横移符号={LATERAL_COMMAND_SIGN:+d}）")
        yaw_cmd, des_cmd = heading_command(yaw_deg, hold_yaw_deg)
        sender.send(motion_channels(lateral=lateral, forward=forward),
                     yaw=yaw_cmd, des_yaw=des_cmd)
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
                if not all(math.isfinite(v) for v in (x, y, yaw)):
                    raise NavigationError(f"{path} 中存在非法点位：{line.strip()}")
                if kind == "origin":
                    origin = (x, y, yaw)
                elif kind == "target":
                    targets.append((x, y, yaw))
    except FileNotFoundError:
        pass
    return origin, targets


def wait_future(future, timeout):
    """仅等待后台 executor 完成 Future，禁止把节点加入第二个 executor。"""
    done = threading.Event()
    future.add_done_callback(lambda _: done.set())
    deadline = time.monotonic() + timeout
    while not future.done():
        remaining = deadline - time.monotonic()
        if remaining <= 0.0 or not rclpy.ok():
            return False
        done.wait(min(remaining, 0.05))
    return True


def cancel_late_goal(future):
    if not future.cancelled() and future.exception() is None:
        handle = future.result()
        if handle is not None and handle.accepted:
            handle.cancel_goal_async()


def plan_path(plan_client, localizer, gx, gy, timeout=10.0):
    """用 Nav2 规划路径；失败/超时抛错，禁止静默退回无绕障直行。"""
    cx, cy, yaw, _ = fresh_pose(localizer)
    goal = ComputePathToPose.Goal()
    goal.start = PoseStamped()
    goal.start.header.frame_id = "map"
    goal.start.pose.position.x = float(cx)
    goal.start.pose.position.y = float(cy)
    goal.start.pose.orientation.z = math.sin(yaw / 2.0)
    goal.start.pose.orientation.w = math.cos(yaw / 2.0)
    goal.start.header.stamp = localizer.get_clock().now().to_msg()
    goal.goal = PoseStamped()
    goal.goal.header.frame_id = "map"
    goal.goal.pose.position.x = float(gx)
    goal.goal.pose.position.y = float(gy)
    goal.goal.pose.orientation.w = 1.0
    goal.goal.header.stamp = goal.start.header.stamp
    goal.use_start = True
    goal.planner_id = "GridBased"

    future = plan_client.send_goal_async(goal)
    if not wait_future(future, 3.0):
        future.add_done_callback(cancel_late_goal)
        raise NavigationError("Nav2 接收规划请求超时")
    goal_handle = future.result()
    if goal_handle is None or not goal_handle.accepted:
        raise NavigationError("Nav2 拒绝规划请求")

    result_future = goal_handle.get_result_async()
    if not wait_future(result_future, timeout):
        goal_handle.cancel_goal_async()
        raise NavigationError("Nav2 规划超时，已请求取消")
    resp = result_future.result()
    if resp is None or resp.status != GoalStatus.STATUS_SUCCEEDED or resp.result is None:
        raise NavigationError(f"Nav2 规划失败，action 状态={getattr(resp, 'status', None)}")
    if getattr(resp.result, "error_code", 0) != 0:
        raise NavigationError(f"Nav2 规划错误码：{resp.result.error_code}")
    path = resp.result.path
    if path is None or not path.poses:
        raise NavigationError("Nav2 返回空路径")
    if path.header.frame_id != "map":
        raise NavigationError(f"路径坐标系不是 map：{path.header.frame_id}")
    points = [(p.pose.position.x, p.pose.position.y) for p in path.poses]
    if not all(math.isfinite(v) for point in points for v in point):
        raise NavigationError("规划路径包含非法坐标")
    if math.hypot(points[-1][0] - gx, points[-1][1] - gy) > STOP_DISTANCE:
        raise NavigationError("规划终点偏离目标超过到达容差，请检查目标是否落在障碍物内")
    fresh_pose(localizer)  # 规划期间定位也必须保持更新
    return points


def path_point(waypoints, lengths, distance):
    if distance >= lengths[-1]:
        return waypoints[-1]
    index = bisect.bisect_right(lengths, distance) - 1
    fraction = (distance - lengths[index]) / (lengths[index + 1] - lengths[index])
    x0, y0 = waypoints[index]
    x1, y1 = waypoints[index + 1]
    return x0 + fraction * (x1 - x0), y0 + fraction * (y1 - y0)


def nearest_path_progress(waypoints, lengths, x, y, progress):
    best_progress = progress
    best_error = math.inf
    for index in range(len(waypoints) - 1):
        if lengths[index + 1] < progress - 0.1 or lengths[index] > progress + 0.75:
            continue
        x0, y0 = waypoints[index]
        x1, y1 = waypoints[index + 1]
        dx, dy = x1 - x0, y1 - y0
        fraction = max(0.0, min(1.0, ((x - x0) * dx + (y - y0) * dy) /
                                 (dx * dx + dy * dy)))
        px, py = x0 + fraction * dx, y0 + fraction * dy
        distance = math.hypot(x - px, y - py)
        candidate = lengths[index] + fraction * (lengths[index + 1] - lengths[index])
        if distance < best_error and candidate >= progress - 0.1:
            best_error = distance
            best_progress = max(progress, candidate)
    return best_progress, best_error


def path_has_bend(waypoints, lengths, progress):
    a = path_point(waypoints, lengths, progress)
    b = path_point(waypoints, lengths, min(lengths[-1], progress + 0.15))
    c = path_point(waypoints, lengths, min(lengths[-1], progress + PATH_LOOKAHEAD))
    first = (b[0] - a[0], b[1] - a[1])
    second = (c[0] - b[0], c[1] - b[1])
    norm = math.hypot(*first) * math.hypot(*second)
    return norm > 1e-9 and first[0] * second[0] + first[1] * second[1] < norm * math.cos(math.radians(35))


def follow_path_transit(sender, localizer, waypoints, hold_yaw_deg,
                        body_yaw_offset_deg, max_speed, max_lateral_speed):
    points = [waypoints[0]]
    for point in waypoints[1:]:
        if math.dist(point, points[-1]) > 1e-6:
            points.append(point)
    lengths = [0.0]
    for start, end in zip(points, points[1:]):
        lengths.append(lengths[-1] + math.dist(start, end))

    progress = 0.0
    deadline = time.monotonic() + max(30.0, lengths[-1] / 0.2)
    last_print = -math.inf
    while True:
        if time.monotonic() > deadline:
            sender.stop()
            raise NavigationError("路径跟踪超时；检查定位及底盘响应")
        try:
            cx, cy, yaw, _ = fresh_pose(localizer)
        except NavigationError:
            sender.stop()
            raise
        progress, path_error = nearest_path_progress(points, lengths, cx, cy, progress)
        remaining = lengths[-1] - progress
        if remaining <= PATH_LOOKAHEAD and math.hypot(
                points[-1][0] - cx, points[-1][1] - cy) <= STOP_DISTANCE:
            sender.stop()
            return

        bend = path_has_bend(points, lengths, progress)
        lookahead = 0.2 if bend else PATH_LOOKAHEAD
        tx, ty = path_point(points, lengths, min(lengths[-1], progress + lookahead))
        dx, dy = tx - cx, ty - cy
        distance = math.hypot(dx, dy)
        forward_err, lateral_err = world_error_to_body(
            dx, dy, yaw, body_yaw_offset_deg)
        speed = min(PID_KP * distance, max_speed)
        if bend:
            speed = min(speed, max_speed * 0.6)
        if path_error > 0.2:
            speed = min(speed, max_speed * 0.5)
        forward = speed * forward_err / distance if distance > 1e-6 else 0.0
        lateral = (LATERAL_COMMAND_SIGN * speed * lateral_err / distance *
                   max_lateral_speed / max_speed) if distance > 1e-6 else 0.0
        lateral = max(-max_lateral_speed, min(max_lateral_speed, lateral))
        if time.monotonic() - last_print >= 1.0:
            last_print = time.monotonic()
            print(f"  连续路径跟踪：剩余={remaining:.2f}m 偏离路径={path_error:.2f}m "
                  f"ch2={int(forward):+d} ch0={int(lateral):+d}")
        yaw_cmd, des_cmd = heading_command(math.degrees(yaw), hold_yaw_deg)
        sender.send(motion_channels(lateral=lateral, forward=forward),
                    yaw=yaw_cmd, des_yaw=des_cmd)
        time.sleep(1.0 / FRAME_HZ)


def follow_path(sender, localizer, waypoints, gx, gy, target_yaw_deg, *,
                body_yaw_offset_deg=0.0,
                max_speed=DEFAULT_FORWARD_SPEED,
                max_lateral_speed=DEFAULT_LATERAL_SPEED):
    """全向底盘保持起始朝向跟踪路径，最后再对准目标朝向。"""
    if not waypoints:
        raise NavigationError("没有可执行的路径")
    if math.hypot(waypoints[-1][0] - gx, waypoints[-1][1] - gy) > STOP_DISTANCE:
        raise NavigationError("规划路径终点偏离目标，不能执行")
    _, _, yaw, _ = fresh_pose(localizer)
    hold_yaw_deg = math.degrees(yaw)
    follow_path_transit(sender, localizer, waypoints, hold_yaw_deg,
                        body_yaw_offset_deg=body_yaw_offset_deg,
                        max_speed=max_speed,
                        max_lateral_speed=max_lateral_speed)
    cx, cy, _, _ = fresh_pose(localizer)
    if math.hypot(gx - cx, gy - cy) > FINAL_CORRECTION_MAX_DISTANCE:
        raise NavigationError("路径执行结束，但实际位置偏离目标超过回正范围")
    # 原地转向可能使全向底盘漂移。回正位置后再复核朝向，直到两者同时达标。
    for attempt in range(1, FINAL_CORRECTION_ATTEMPTS + 1):
        cx, cy, yaw, _ = fresh_pose(localizer)
        distance = math.hypot(gx - cx, gy - cy)
        yaw_error = abs(norm_deg(target_yaw_deg - math.degrees(yaw)))

        if distance > FINAL_POSITION_TOLERANCE:
            print(f"  最终位置回正 {attempt}/{FINAL_CORRECTION_ATTEMPTS}："
                  f"当前误差={distance:.3f}m，目标≤{FINAL_POSITION_TOLERANCE:.2f}m")
            if not pid_drive_to(
                    sender, localizer, gx, gy, target_yaw_deg,
                    tolerance=FINAL_POSITION_TOLERANCE,
                    body_yaw_offset_deg=body_yaw_offset_deg,
                    max_speed=min(max_speed, FINAL_CORRECTION_SPEED),
                    max_lateral_speed=min(max_lateral_speed, FINAL_CORRECTION_SPEED)):
                raise NavigationError("最终位置回正失败，未完成导航")

        _, _, yaw, _ = fresh_pose(localizer)
        yaw_error = abs(norm_deg(target_yaw_deg - math.degrees(yaw)))
        if yaw_error > TURN_TOL_DEG:
            if not pid_turn_to(sender, localizer, target_yaw_deg):
                raise NavigationError("目标朝向调整失败，未完成导航")

        cx, cy, yaw, _ = fresh_pose(localizer)
        distance = math.hypot(gx - cx, gy - cy)
        yaw_error = abs(norm_deg(target_yaw_deg - math.degrees(yaw)))
        if (distance <= FINAL_POSITION_TOLERANCE and
                yaw_error <= TURN_TOL_DEG):
            sender.stop()
            print(f"  到达复核：位置误差={distance:.3f}m，"
                  f"角度误差={yaw_error:.1f}°")
            return
        print(f"  复核未同时达标：位置误差={distance:.3f}m，"
              f"角度误差={yaw_error:.1f}°，继续回正")

    sender.stop()
    raise NavigationError(
        f"最终复核未通过：位置误差={distance:.3f}m，"
        f"角度误差={yaw_error:.1f}°")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    check_modes = parser.add_mutually_exclusive_group()
    check_modes.add_argument("--check-only", action="store_true",
                        help="只检查实时定位和所有目标的规划，不连接下位机、不发运动帧")
    check_modes.add_argument("--check-localization", action="store_true",
                            help="预热 3 秒后静止采样 10 秒，对比两路定位；不连接底盘")
    parser.add_argument("--body-yaw-offset-deg", type=float,
                        default=DEFAULT_BODY_YAW_OFFSET_DEG,
                        help=f"定位 yaw 到底盘前向的角度偏差；当前默认 {DEFAULT_BODY_YAW_OFFSET_DEG:g}°")
    parser.add_argument("--max-speed", type=int, default=DEFAULT_FORWARD_SPEED,
                        help=f"前后通道幅值上限，1～{PID_MAX_SPEED}；不是米/秒")
    parser.add_argument("--max-lateral-speed", type=int,
                        default=DEFAULT_LATERAL_SPEED,
                        help=f"横移通道幅值上限，1～{PID_MAX_SPEED}；"
                             f"默认 {DEFAULT_LATERAL_SPEED}")
    args = parser.parse_args(remove_ros_args()[1:])
    if not math.isfinite(args.body_yaw_offset_deg):
        parser.error("车体朝向偏角必须是有限数值")
    if not 1 <= args.max_speed <= PID_MAX_SPEED:
        parser.error(f"--max-speed 必须在 1～{PID_MAX_SPEED} 之间")
    if not 1 <= args.max_lateral_speed <= PID_MAX_SPEED:
        parser.error(f"--max-lateral-speed 必须在 1～{PID_MAX_SPEED} 之间")
    args.body_yaw_offset_deg = norm_deg(args.body_yaw_offset_deg)
    if args.check_localization:
        return check_localization()
    rclpy.init()
    localizer = Localizer()
    executor = SingleThreadedExecutor()
    executor.add_node(localizer)
    spin_thread = threading.Thread(target=executor.spin, daemon=True)
    spin_thread.start()

    # Nav2 规划器客户端
    plan_client = ActionClient(localizer, ComputePathToPose, PLAN_ACTION)

    sender = None
    try:
        # 等定位
        print(f"等待 {ROBOT_ODOM_TOPIC} ...")
        t0 = time.monotonic()
        while time.monotonic() - t0 < 30.0:
            try:
                fresh_pose(localizer)
                print("✅ 定位就绪")
                break
            except NavigationError:
                pass
            time.sleep(0.1)
        else:
            raise NavigationError(f"30 秒没收到有效 {ROBOT_ODOM_TOPIC}，请确认雷达驱动 + Super-LIO 已启动")

        # 首帧可能来自启动阶段的定位缓存/初始匹配；稳定后再读取位置和规划。
        print(f"定位首帧已收到，等待 {INITIAL_POSE_SETTLE_SEC:.1f}s 稳定后再规划...")
        time.sleep(INITIAL_POSE_SETTLE_SEC)
        fresh_pose(localizer)

        # ③ 打印起始坐标 + 目标坐标
        origin, targets = load_points(POINTS_FILE)
        if origin is not None:
            print(f"起始坐标：({origin[0]:.3f}, {origin[1]:.3f}, 朝向 {origin[2]:.1f}°)")
        else:
            print("⚠️ 未找到起始点")
        if not targets:
            if args.check_only:
                raise NavigationError(f"没有目标点：{POINTS_FILE}")
            print(f"⚠️ 没有目标点（{POINTS_FILE} 为空），手动输入：")
            try:
                x = float(input("  目标 x："))
                y = float(input("  目标 y："))
                yaw = float(input("  目标朝向（度）："))
                targets = [(x, y, yaw)]
            except ValueError:
                raise NavigationError("目标输入不是有效数值")
        for i, (x, y, yaw_deg) in enumerate(targets, 1):
            if not all(math.isfinite(v) for v in (x, y, yaw_deg)):
                raise NavigationError("目标点包含 NaN/Inf")
            print(f"目标坐标 #{i}：({x:.3f}, {y:.3f}, 朝向 {yaw_deg:.1f}°)")
        cx, cy, yaw, _ = fresh_pose(localizer)
        print(f"当前实时定位：({cx:.3f}, {cy:.3f}, 朝向 {math.degrees(yaw):.1f}°)")
        print("注意：上面的记录起点不代表当前定位；重定位必须与建图时使用同一张地图。")
        print(f"车体前向偏角={args.body_yaw_offset_deg:.1f}°，"
              f"当前车体yaw={norm_deg(math.degrees(yaw) + args.body_yaw_offset_deg):.1f}°，"
              f"前后上限={args.max_speed}，横移上限={args.max_lateral_speed}；"
              f"目标朝向保留原定位坐标系。")

        # ④ 确认是否开始导航
        if not args.check_only:
            resp = input("\n是否开始导航至目标点位? (y/n): ").strip().lower()
            if resp != "y":
                print("已取消导航")
                return 0

        # ⑤ 等 Nav2 规划器
        print(f"等待 Nav2 规划器 {PLAN_ACTION} ...")
        nav_available = plan_client.wait_for_server(timeout_sec=10.0)
        if not nav_available:
            raise NavigationError("Nav2 规划器未就绪，停止导航（不会退回无绕障直行）")
        print("✅ Nav2 规划器就绪")
        fresh_pose(localizer)
        if args.check_only:
            for i, (x, y, _) in enumerate(targets, 1):
                points = plan_path(plan_client, localizer, x, y)
                cx, cy, yaw, _ = fresh_pose(localizer)
                print(f"✅ 目标 #{i}：{len(points)} 个路径点；规划后实时定位 "
                      f"({cx:.3f}, {cy:.3f}, {math.degrees(yaw):.1f}°)")
                print_direction_preview(points, localizer, args.body_yaw_offset_deg,
                                        goal=(x, y))
            print("检查完成；未连接下位机，未发送运动帧。此检查不验证实际车体方向。")
            return 0

        # ⑥ 连接下位机
        sender = Sender()
        sender.stop()

        print(f"\n开始依次到达 {len(targets)} 个目标点...")
        for i, (x, y, yaw_deg) in enumerate(targets, 1):
            print(f"\n>> 目标 #{i}：({x:.3f}, {y:.3f}, {yaw_deg:.1f}°)")

            waypoints = plan_path(plan_client, localizer, x, y)
            print(f"  Nav2 规划出 {len(waypoints)} 个路径点，保持起始朝向沿路径行走")
            print_direction_preview(waypoints, localizer, args.body_yaw_offset_deg,
                                    goal=(x, y))
            follow_path(sender, localizer, waypoints, x, y, yaw_deg,
                        body_yaw_offset_deg=args.body_yaw_offset_deg,
                        max_speed=args.max_speed,
                        max_lateral_speed=args.max_lateral_speed)
            print(f">> 目标 #{i} 到达 ✅")

        print("\n导航结束")
        return 0

    except KeyboardInterrupt:
        print("\n🛑 Ctrl+C 急停")
        return 130
    except Exception as e:
        print(f"❌ 出错：{e}")
        return 1
    finally:
        if sender is not None:
            sender.close()
        executor.shutdown()
        spin_thread.join(timeout=1.0)
        plan_client.destroy()
        localizer.destroy_node()
        rclpy.try_shutdown()
        print("已安全退出")


if __name__ == "__main__":
    sys.exit(main())
