#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
demo_mid360_pickpoint_enhanced.py —— 增强版：支持手动遥控

新增功能：
    手动遥控模式 - 边建图边遥控移动，边打点

菜单：
    【建图】 m 开始   n 停止   s 保存 PCD
    【打点】 a 记录   w 手动   l 列表   K 清空
             p 保存 JSON   o 加载 JSON
    【遥控】 c 进入遥控模式（WASD控制+打点）
    【导航】 g 依次导航
    【其他】 1 手动重定位   5 状态   6 急停   q 退出
"""

import json
import math
import os
import socket
import struct
import threading
import time
import sys
import termios
import tty
import select
from datetime import datetime
from typing import Optional, Tuple, List, Dict

import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from nav_msgs.msg import Odometry, OccupancyGrid
from sensor_msgs.msg import PointCloud2
try:
    from sensor_msgs_py import point_cloud2
    _HAS_PC2 = True
except ImportError:
    _HAS_PC2 = False
from tf2_msgs.msg import TFMessage


# ==================== 网络 ====================
TCP_IP = "192.168.2.199"
TCP_PORT = 5000

# ==================== 帧协议 ====================
SOF1 = 0xA5
SOF2 = 0x5A
LEN = 0x1C
TYPE = 0x01
SAFE_SWITCH = 1
FRAME_HZ = 70
CTRL_HZ = 50
CHANNEL_COUNT = 10

# ==================== 话题 ====================
ODOM_TOPIC = "/lio/robo/odom"
CLOUD_TOPIC = "/cloud_registered"
MAP_TOPIC = "/map"

# ==================== 文件路径 ====================
MAP_SAVE_DIR = "./maps"
WAYPOINT_SAVE_DIR = "./waypoints"

# ==================== 运动参数 ====================
SPEED_FORWARD = 300
SPEED_NEAR = 150
SPEED_FINE = 80
NEAR_DIST = 0.30
FINE_DIST = 0.10

MOVE_KP = 800.0
STOP_DISTANCE = 0.010
TURN_TOL_DEG = 0.5
TURN_STABLE_SEC = 0.30

TURN_TIMEOUT = 15.0
MOVE_TIMEOUT = 40.0
FINE_TUNE_MAX_ITER = 5
FINE_TUNE_TOL = 0.008

# ==================== 遥控参数 ====================
MANUAL_SPEED_FORWARD = 200    # 前进速度
MANUAL_SPEED_BACKWARD = -200  # 后退速度
MANUAL_SPEED_TURN = 150       # 转向速度
MANUAL_SPEED_LATERAL = 150    # 横向速度

# ==================== 坐标系 ====================
YAW_OFFSET_DEG = 0.0


# ==================== 帧组装 ====================

def crc16_ccitt(data: bytes) -> int:
    crc = 0xFFFF
    for b in data:
        crc ^= (b << 8)
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
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
    ch = [0, 0, 0, 0] + [SAFE_SWITCH] * (CHANNEL_COUNT - 4)
    ch[0] = int(lateral)
    ch[2] = int(forward)
    ch[3] = int(rotation)
    return ch


def quat_to_yaw(qx, qy, qz, qw) -> float:
    return math.atan2(2.0 * (qw * qz + qx * qy), 1.0 - 2.0 * (qy * qy + qz * qz))


def norm_deg(d: float) -> float:
    while d > 180.0:
        d -= 360.0
    while d < -180.0:
        d += 360.0
    return d


def yaw_deg_to_i16(d: float) -> int:
    return int(round(d * 100.0))


# ==================== TCP 发送线程 ====================

class SenderThread:
    def __init__(self, tcp_ip=TCP_IP, tcp_port=TCP_PORT, hz=FRAME_HZ):
        self.tcp_ip = tcp_ip
        self.tcp_port = tcp_port
        self.period = 1.0 / float(hz)
        self.sock: Optional[socket.socket] = None
        self.seq = 0
        self._lock = threading.Lock()
        self._running = False
        self._thread: Optional[threading.Thread] = None

        self._lateral = 0
        self._forward = 0
        self._rotation = 0
        self._yaw_i16 = 0
        self._des_yaw_i16 = 0

    def connect(self):
        print(f"连接下位机 {self.tcp_ip}:{self.tcp_port} ...")
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(3.0)
        self.sock.connect((self.tcp_ip, self.tcp_port))
        self.sock.settimeout(None)
        print("✅ TCP 已连接")

    def set_state(self, lateral=0, forward=0, rotation=0,
                  yaw_i16=None, des_yaw_i16=None):
        with self._lock:
            self._lateral = int(lateral)
            self._forward = int(forward)
            self._rotation = int(rotation)
            if yaw_i16 is not None:
                self._yaw_i16 = int(yaw_i16)
            if des_yaw_i16 is not None:
                self._des_yaw_i16 = int(des_yaw_i16)

    def stop(self):
        self.set_state(0, 0, 0, yaw_i16=0, des_yaw_i16=0)

    def start(self):
        if self._running:
            return
        self._running = True
        self._thread = threading.Thread(target=self._loop, daemon=True)
        self._thread.start()

    def _loop(self):
        next_t = time.time()
        while self._running:
            with self._lock:
                lat, fwd, rot = self._lateral, self._forward, self._rotation
                yaw_i16, des_yaw_i16 = self._yaw_i16, self._des_yaw_i16
            frame = build_frame(self.seq, motion_channels(lat, fwd, rot),
                                yaw_i16, des_yaw_i16)
            try:
                self.sock.sendall(frame)
                self.seq = (self.seq + 1) & 0xFFFF
            except Exception as e:
                print(f"⚠️ 发送失败：{e}")
                time.sleep(0.1)
                continue
            next_t += self.period
            dt = next_t - time.time()
            if dt > 0:
                time.sleep(dt)
            else:
                next_t = time.time()

    def close(self):
        self._running = False
        if self._thread:
            self._thread.join(timeout=1.0)
        try:
            self.sock.sendall(build_frame(self.seq, motion_channels(0, 0, 0)))
        except Exception:
            pass
        try:
            if self.sock:
                self.sock.close()
        except Exception:
            pass


# ==================== ROS2 定位 + 建图节点 ====================

class Localizer(Node):
    def __init__(self):
        super().__init__("pick_point_localizer")
        self._lock = threading.Lock()

        self._map_to_odom: Optional[Tuple[float, float, float]] = None
        self._odom_to_base: Optional[Tuple[float, float, float]] = None
        self._last_odom_wall_t = 0.0
        self._last_tf_wall_t = 0.0

        self._manual_offset = (0.0, 0.0)
        self._use_manual_offset = False
        self.map_info: Optional[dict] = None

        self._mapping = False
        self._map_points: List[Tuple[float, float, float]] = []
        self._cloud_frame_count = 0
        self._last_cloud_wall_t = 0.0

        self.create_subscription(TFMessage, "/tf", self._tf_cb, 100)
        self.create_subscription(Odometry, ODOM_TOPIC, self._odom_cb, 10)
        self.create_subscription(OccupancyGrid, MAP_TOPIC, self._map_cb, 10)
        if _HAS_PC2:
            self.create_subscription(PointCloud2, CLOUD_TOPIC, self._cloud_cb, 10)

    def _tf_cb(self, msg: TFMessage):
        with self._lock:
            for tf in msg.transforms:
                p, c = tf.header.frame_id, tf.child_frame_id
                if p == "map" and c == "odom":
                    self._map_to_odom = (
                        tf.transform.translation.x,
                        tf.transform.translation.y,
                        quat_to_yaw(tf.transform.rotation.x,
                                    tf.transform.rotation.y,
                                    tf.transform.rotation.z,
                                    tf.transform.rotation.w),
                    )
                    self._last_tf_wall_t = time.time()

    def _odom_cb(self, msg: Odometry):
        p = msg.pose.pose
        with self._lock:
            self._odom_to_base = (
                float(p.position.x),
                float(p.position.y),
                quat_to_yaw(p.orientation.x, p.orientation.y,
                            p.orientation.z, p.orientation.w),
            )
            self._last_odom_wall_t = time.time()

    def _map_cb(self, msg: OccupancyGrid):
        self.map_info = {
            "width": msg.info.width,
            "height": msg.info.height,
            "resolution": msg.info.resolution,
            "origin": (msg.info.origin.position.x, msg.info.origin.position.y),
        }

    def set_manual_offset(self, x0, y0):
        p = self.get_pose()
        if p is None:
            return False
        cx, cy, _ = p
        self._manual_offset = (x0 - cx, y0 - cy)
        self._use_manual_offset = True
        print(f"✅ 手动 offset：({self._manual_offset[0]:+.3f}, {self._manual_offset[1]:+.3f})")
        return True

    def get_pose(self):
        with self._lock:
            if self._odom_to_base is None:
                return None
            obx, oby, obyaw = self._odom_to_base
            if self._map_to_odom is not None:
                ox, oy, oyaw = self._map_to_odom
                mx = ox + obx * math.cos(oyaw) - oby * math.sin(oyaw)
                my = oy + obx * math.sin(oyaw) + oby * math.cos(oyaw)
                myaw = oyaw + obyaw
            elif self._use_manual_offset:
                mx = obx + self._manual_offset[0]
                my = oby + self._manual_offset[1]
                myaw = obyaw
            else:
                mx, my, myaw = obx, oby, obyaw
        return mx, my, norm_deg(math.degrees(myaw) + YAW_OFFSET_DEG)

    def pose_age(self):
        with self._lock:
            return time.time() - self._last_odom_wall_t

    # ---------- 建图 ----------

    def start_mapping(self):
        if not _HAS_PC2:
            print("❌ 没有 sensor_msgs_py 包，无法建图")
            return
        with self._lock:
            self._mapping = True
            self._map_points = []
            self._cloud_frame_count = 0
        print("📡 建图已开始，推车扫场...")

    def stop_mapping(self):
        with self._lock:
            self._mapping = False
            n = len(self._map_points)
            frames = self._cloud_frame_count
        print(f"📡 建图已停止，共 {n:,} 点 / {frames} 帧")
        return n

    def mapping_status(self):
        with self._lock:
            return {
                "mapping": self._mapping,
                "points": len(self._map_points),
                "frames": self._cloud_frame_count,
                "cloud_age": (time.time() - self._last_cloud_wall_t
                              if self._last_cloud_wall_t > 0 else None),
            }

    def _cloud_cb(self, msg: PointCloud2):
        with self._lock:
            self._last_cloud_wall_t = time.time()
            if not self._mapping:
                return
        try:
            pts = list(point_cloud2.read_points(
                msg, field_names=("x", "y", "z"), skip_nans=True))
        except Exception:
            return
        with self._lock:
            if not self._mapping:
                return
            for p in pts:
                self._map_points.append((float(p[0]), float(p[1]), float(p[2])))
            self._cloud_frame_count += 1

    def save_pcd(self, path):
        with self._lock:
            pts = list(self._map_points)
        n = len(pts)
        if n == 0:
            print("❌ 没有点云，无法保存")
            return False
        os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
        with open(path, "w") as f:
            f.write("# .PCD v0.7 - Point Cloud Data file format\n")
            f.write("VERSION 0.7\n")
            f.write("FIELDS x y z\n")
            f.write("SIZE 4 4 4\n")
            f.write("TYPE F F F\n")
            f.write("COUNT 1 1 1\n")
            f.write(f"WIDTH {n}\n")
            f.write("HEIGHT 1\n")
            f.write("VIEWPOINT 0 0 0 1 0 0 0\n")
            f.write(f"POINTS {n}\n")
            f.write("DATA ascii\n")
            for x, y, z in pts:
                f.write(f"{x:.6f} {y:.6f} {z:.6f}\n")
        print(f"✅ PCD 已保存：{path}（{n:,} 点）")
        return True


# ==================== 打点存储 ====================

class WaypointStore:
    def __init__(self):
        self.targets: List[Dict] = []

    def add(self, name: str, x: float, y: float, yaw: float):
        self.targets.append({
            "name": str(name),
            "x": float(x), "y": float(y), "yaw": float(yaw),
        })
        return len(self.targets)

    def save(self, path: str):
        os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
        with open(path, "w") as f:
            json.dump({"targets": self.targets}, f,
                      ensure_ascii=False, indent=2)
        print(f"✅ 已保存 {len(self.targets)} 个目标点到 {path}")

    def load(self, path: str):
        with open(path, "r") as f:
            data = json.load(f)
        self.targets = []
        for t in data.get("targets", []):
            self.targets.append({
                "name": str(t.get("name", "point")),
                "x": float(t["x"]), "y": float(t["y"]),
                "yaw": float(t.get("yaw", 0.0)),
            })
        print(f"✅ 已加载 {len(self.targets)} 个目标点")

    def clear(self):
        self.targets = []
        print("🗑️ 已清空目标点")

    def show(self):
        if not self.targets:
            print("  （无目标点）")
            return
        for i, t in enumerate(self.targets, 1):
            print(f"  #{i}「{t['name']}」: x={t['x']:.3f} "
                  f"y={t['y']:.3f} yaw={t['yaw']:+.1f}°")


# ==================== 导航器 ====================

class Navigator:
    def __init__(self, loc: Localizer, sender: SenderThread):
        self.loc = loc
        self.sender = sender

    def _wait_pose(self, timeout=2.0):
        t0 = time.time()
        while time.time() - t0 < timeout:
            p = self.loc.get_pose()
            if p is not None:
                return p
            time.sleep(0.02)
        return None

    def _send(self, lat=0, fwd=0, rot=0, cur_yaw=None, des_yaw=None):
        self.sender.set_state(
            lateral=lat, forward=fwd, rotation=rot,
            yaw_i16=None if cur_yaw is None else yaw_deg_to_i16(cur_yaw),
            des_yaw_i16=None if des_yaw is None else yaw_deg_to_i16(des_yaw),
        )

    def turn_to(self, target_yaw_deg, tol_deg=TURN_TOL_DEG, timeout=TURN_TIMEOUT):
        start = time.time()
        in_tol_since: Optional[float] = None
        while True:
            if time.time() - start > timeout:
                self.sender.stop()
                print("  ⚠️ 转向超时")
                return False
            p = self.loc.get_pose()
            if p is None:
                time.sleep(0.02)
                continue
            _, _, cur_yaw = p
            err = norm_deg(target_yaw_deg - cur_yaw)
            if abs(err) <= tol_deg:
                if in_tol_since is None:
                    in_tol_since = time.time()
                elif time.time() - in_tol_since >= TURN_STABLE_SEC:
                    self._send(0, 0, 0, cur_yaw, target_yaw_deg)
                    return True
            else:
                in_tol_since = None
            self._send(0, 0, 0, cur_yaw, target_yaw_deg)
            time.sleep(1.0 / CTRL_HZ)

    def drive_to(self, tx, ty, hold_yaw_deg, timeout=MOVE_TIMEOUT):
        start = time.time()
        while True:
            if time.time() - start > timeout:
                self.sender.stop()
                print("  ⚠️ 直行超时")
                return False
            p = self.loc.get_pose()
            if p is None:
                time.sleep(0.02)
                continue
            cx, cy, cur_yaw = p
            dist = math.hypot(tx - cx, ty - cy)
            if dist < STOP_DISTANCE:
                self._send(0, 0, 0, cur_yaw, hold_yaw_deg)
                return True

            if dist < FINE_DIST:
                cap = SPEED_FINE
            elif dist < NEAR_DIST:
                cap = SPEED_NEAR
            else:
                cap = SPEED_FORWARD

            raw = MOVE_KP * dist
            fwd = max(60, min(raw, cap))
            self._send(fwd=fwd, cur_yaw=cur_yaw, des_yaw=hold_yaw_deg)
            time.sleep(1.0 / CTRL_HZ)

    def fine_tune(self, tx, ty, hold_yaw_deg):
        for it in range(FINE_TUNE_MAX_ITER):
            p = self.loc.get_pose()
            if p is None:
                return False
            cx, cy, cur_yaw = p
            dx, dy = tx - cx, ty - cy
            dist = math.hypot(dx, dy)
            if dist < FINE_TUNE_TOL:
                print(f"  ✅ 精调完成 第{it+1}轮 误差={dist*1000:.1f}mm")
                return True

            cyaw_rad = math.radians(cur_yaw)
            fwd_err = math.cos(cyaw_rad) * dx + math.sin(cyaw_rad) * dy
            lat_err = -math.sin(cyaw_rad) * dx + math.cos(cyaw_rad) * dy
            f_cmd = max(-60, min(60, fwd_err * 600))
            l_cmd = max(-60, min(60, lat_err * 600))

            for _ in range(6):
                self._send(fwd=f_cmd, lat=l_cmd,
                           cur_yaw=cur_yaw, des_yaw=hold_yaw_deg)
                time.sleep(1.0 / FRAME_HZ)
            self._send(0, 0, 0, cur_yaw, hold_yaw_deg)
            time.sleep(0.20)
        return False

    def goto(self, x, y, yaw_deg):
        p = self._wait_pose(2.0)
        if p is None:
            print("❌ 无定位")
            return False
        cx, cy, _ = p
        approach_yaw = math.degrees(math.atan2(y - cy, x - cx))
        print(f"  ① 转向面对目标：{approach_yaw:+.1f}°")
        if not self.turn_to(approach_yaw):
            return False
        print(f"  ② 直行至 ({x:.3f}, {y:.3f})")
        if not self.drive_to(x, y, approach_yaw):
            return False
        print(f"  ③ 精调")
        self.fine_tune(x, y, approach_yaw)
        if abs(norm_deg(yaw_deg - approach_yaw)) > TURN_TOL_DEG:
            print(f"  ④ 转到目标朝向：{yaw_deg:+.1f}°")
            if not self.turn_to(yaw_deg):
                return False
        print("  ✅ 到达")
        return True


# ==================== 手动遥控模式 ====================

def get_key_non_blocking():
    """非阻塞获取按键"""
    if select.select([sys.stdin], [], [], 0)[0]:
        return sys.stdin.read(1)
    return None


def manual_control_mode(loc: Localizer, sender: SenderThread, store: WaypointStore):
    """手动遥控模式 - WASD控制 + 空格打点"""
    print("\n" + "="*60)
    print("🎮 手动遥控模式")
    print("="*60)
    print("  W - 前进")
    print("  S - 后退")
    print("  A - 左转")
    print("  D - 右转")
    print("  Q - 左平移")
    print("  E - 右平移")
    print("  空格 - 快速打点（自动命名）")
    print("  P - 打点并输入名称")
    print("  X - 急停")
    print("  ESC - 退出遥控模式")
    print("="*60)
    print("\n💡 提示：可以边建图(m)边遥控，边打点\n")

    # 保存终端设置
    old_settings = termios.tcgetattr(sys.stdin)

    try:
        # 设置终端为原始模式（立即响应按键）
        tty.setcbreak(sys.stdin.fileno())

        lateral = 0
        forward = 0
        rotation = 0

        last_status_print = time.time()

        while True:
            # 非阻塞读取按键
            key = get_key_non_blocking()

            # 重置控制量
            lateral = 0
            forward = 0
            rotation = 0

            if key:
                key_lower = key.lower()

                # ESC键退出
                if ord(key) == 27:  # ESC
                    break

                # 运动控制
                elif key_lower == 'w':
                    forward = MANUAL_SPEED_FORWARD
                    print("\r↑ 前进    ", end='', flush=True)
                elif key_lower == 's':
                    forward = MANUAL_SPEED_BACKWARD
                    print("\r↓ 后退    ", end='', flush=True)
                elif key_lower == 'a':
                    rotation = MANUAL_SPEED_TURN
                    print("\r← 左转    ", end='', flush=True)
                elif key_lower == 'd':
                    rotation = -MANUAL_SPEED_TURN
                    print("\r→ 右转    ", end='', flush=True)
                elif key_lower == 'q':
                    lateral = -MANUAL_SPEED_LATERAL
                    print("\r⬅ 左平移  ", end='', flush=True)
                elif key_lower == 'e':
                    lateral = MANUAL_SPEED_LATERAL
                    print("\r➡ 右平移  ", end='', flush=True)

                # 打点
                elif key == ' ':
                    p = loc.get_pose()
                    if p:
                        name = f"waypoint{len(store.targets) + 1}"
                        store.add(name, p[0], p[1], p[2])
                        print(f"\n✅ 快速打点「{name}」: x={p[0]:.3f} y={p[1]:.3f} yaw={p[2]:+.1f}°")
                    else:
                        print("\n❌ 无定位，无法打点")

                elif key_lower == 'p':
                    p = loc.get_pose()
                    if p:
                        print("\n请输入点名: ", end='', flush=True)
                        # 临时恢复终端设置以输入文本
                        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)
                        name = input().strip()
                        tty.setcbreak(sys.stdin.fileno())

                        if not name:
                            name = f"waypoint{len(store.targets) + 1}"
                        store.add(name, p[0], p[1], p[2])
                        print(f"✅ 已打点「{name}」: x={p[0]:.3f} y={p[1]:.3f} yaw={p[2]:+.1f}°\n")
                    else:
                        print("\n❌ 无定位，无法打点\n")

                # 急停
                elif key_lower == 'x':
                    sender.stop()
                    print("\n🛑 急停\n")

            # 发送控制指令
            sender.set_state(lateral=lateral, forward=forward, rotation=rotation)

            # 定期显示状态
            if time.time() - last_status_print > 2.0:
                p = loc.get_pose()
                ms = loc.mapping_status()
                if p:
                    print(f"\n[位置: x={p[0]:.2f} y={p[1]:.2f} yaw={p[2]:+.0f}° | "
                          f"打点: {len(store.targets)} | "
                          f"建图: {'ON' if ms['mapping'] else 'OFF'} "
                          f"({ms['points']//1000}K点)]", end='', flush=True)
                last_status_print = time.time()

            time.sleep(0.05)  # 20Hz更新

        # 退出时停止
        sender.stop()
        print("\n\n退出遥控模式")

    finally:
        # 恢复终端设置
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)


# ==================== 主菜单 ====================

def main():
    rclpy.init()
    loc = Localizer()
    executor = SingleThreadedExecutor()
    executor.add_node(loc)
    threading.Thread(target=executor.spin, daemon=True).start()

    print(f"等待 {ODOM_TOPIC} ...")
    t0 = time.time()
    while time.time() - t0 < 5.0:
        if loc.get_pose() is not None:
            print("✅ 已收到位姿")
            break
        time.sleep(0.1)
    else:
        print(f"❌ 5 秒内未收到 {ODOM_TOPIC}，检查 LIO 是否启动")
        executor.shutdown(); rclpy.shutdown(); return

    sender = SenderThread()
    try:
        sender.connect()
        sender.start()
        sender.stop()
    except Exception as e:
        print(f"❌ TCP 连接失败：{e}")
        executor.shutdown(); rclpy.shutdown(); return

    nav = Navigator(loc, sender)
    store = WaypointStore()

    try:
        while True:
            print("\n" + "=" * 60)
            print(" Mid360 + R2_H 建图 / 打点 / 导航 Demo (增强版)")
            print("=" * 60)
            print(" 【建图】 m 开始   n 停止   s 保存 PCD")
            print(" 【打点】 a 记录   w 手动   l 列表   K 清空")
            print("          p 保存 JSON   o 加载 JSON")
            print(" 【遥控】 c 手动遥控模式 (WASD+空格打点)")
            print(" 【导航】 g 依次导航")
            print(" 【其他】 1 手动重定位   5 状态   6 急停   q 退出")
            print("=" * 60)

            try:
                cmd = input("命令：").strip()
            except (EOFError, KeyboardInterrupt):
                break

            if cmd == "m":
                loc.start_mapping()
            elif cmd == "n":
                loc.stop_mapping()
            elif cmd == "s":
                loc.stop_mapping()
                ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                path = os.path.join(MAP_SAVE_DIR, f"mid360_map_{ts}.pcd")
                loc.save_pcd(path)
                print(f"\n💡 转换为Nav2地图：")
                print(f"   python3 superlio_map_pipeline.py {path} --output-name my_map")

            elif cmd == "a":
                p = loc.get_pose()
                if p is None:
                    print("❌ 无定位"); continue
                name = input("  点名（回车=自动命名）：").strip()
                if not name:
                    name = f"point{len(store.targets) + 1}"
                store.add(name, p[0], p[1], p[2])
                print(f"✅ 已记录「{name}」：x={p[0]:.3f} "
                      f"y={p[1]:.3f} yaw={p[2]:+.1f}°")
            elif cmd == "w":
                try:
                    x = float(input("  x: "))
                    y = float(input("  y: "))
                    yaw = float(input("  yaw(deg): "))
                except ValueError:
                    print("输入错误"); continue
                name = input("  点名（回车=自动命名）：").strip()
                if not name:
                    name = f"point{len(store.targets) + 1}"
                store.add(name, x, y, yaw)
                print(f"✅ 已添加「{name}」")
            elif cmd == "l":
                store.show()
            elif cmd == "K":
                store.clear()
            elif cmd == "p":
                ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                path = os.path.join(WAYPOINT_SAVE_DIR, f"waypoints_{ts}.json")
                store.save(path)
            elif cmd == "o":
                path = input("  文件路径：").strip()
                if not path:
                    print("需要输入路径"); continue
                try:
                    store.load(path)
                except Exception as e:
                    print(f"❌ 加载失败：{e}")

            elif cmd == "c":
                # 进入手动遥控模式
                manual_control_mode(loc, sender, store)

            elif cmd == "g":
                if not store.targets:
                    print("⚠️ 没有目标点"); continue
                for i, t in enumerate(store.targets, 1):
                    print(f"\n>>> 目标 #{i}「{t['name']}」："
                          f"({t['x']:.3f}, {t['y']:.3f}, {t['yaw']:+.1f}°)")
                    if not nav.goto(t["x"], t["y"], t["yaw"]):
                        print(f">>> 目标 #{i} 失败，中断")
                        break
                    print(f">>> 目标 #{i} 到达 ✅")

            elif cmd == "1":
                try:
                    x0 = float(input("  当前地图 x："))
                    y0 = float(input("  当前地图 y："))
                except ValueError:
                    print("输入错误"); continue
                loc.set_manual_offset(x0, y0)

            elif cmd == "5":
                p = loc.get_pose()
                if p:
                    print(f"  当前：x={p[0]:.3f} y={p[1]:.3f} "
                          f"yaw={p[2]:+.1f}° age={loc.pose_age()*1000:.0f}ms")
                else:
                    print("  当前：无定位")
                ms = loc.mapping_status()
                if ms["mapping"]:
                    print(f"  📡 建图中：{ms['points']:,} 点 / {ms['frames']} 帧")
                else:
                    print(f"  📡 建图未开启（累积 {ms['points']:,} 点）")
                if ms["cloud_age"] is None:
                    print(f"  ⚠️ 未收到点云 {CLOUD_TOPIC}")
                if loc.map_info:
                    info = loc.map_info
                    print(f"  2D 地图：{info['width']}x{info['height']} "
                          f"res={info['resolution']}m/cell")
                else:
                    print("  2D 地图：未收到 /map")
                print(f"  目标点：{len(store.targets)} 个")
                store.show()

            elif cmd == "6":
                sender.stop()
                print("🛑 急停")
            elif cmd == "q":
                break
            else:
                print("未知命令")

    except KeyboardInterrupt:
        print("\n🛑 Ctrl+C")
    finally:
        sender.close()
        executor.shutdown()
        rclpy.shutdown()
        print("已退出")


if __name__ == "__main__":
    main()
