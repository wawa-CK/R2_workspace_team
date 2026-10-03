#!/usr/bin/env python3
"""Record new navigation targets from relocation on the existing map."""

import argparse
import math
import os
from pathlib import Path
import shutil
import signal
import subprocess
import tempfile
import time
from datetime import datetime


POINTS_FILE = Path(__file__).resolve().parent / "points.txt"
TF_MAX_AGE_SEC = 0.5


class ManagedLaunch:
    """Own only the process group created for this picking session."""

    def __init__(self, directory):
        self.directory = Path(directory)
        self.process = None

    def __enter__(self):
        log_dir = self.directory / "logs"
        log_dir.mkdir(exist_ok=True)
        stamp = datetime.now().strftime("%Y%m%d-%H%M%S-%f")
        self.log_path = log_dir / f"pick_targets-{stamp}.log"
        with self.log_path.open("w") as stream:
            self.process = subprocess.Popen(
                ["ros2", "launch", str(self.directory / "nav.launch.py"),
                 "start_nav2:=false"],
                stdin=subprocess.DEVNULL, stdout=stream, stderr=subprocess.STDOUT,
                start_new_session=True)
        print(f"正在启动雷达并加载 {self.directory / 'map3d.pcd'}", flush=True)
        print(f"启动和重定位日志：{self.log_path}", flush=True)
        return self

    def check_running(self):
        code = self.process.poll()
        if code is not None:
            tail = "\n".join(self.log_path.read_text(errors="replace").splitlines()[-20:])
            raise RuntimeError(f"雷达/重定位启动程序已退出（{code}）：\n{tail}")

    def _group_alive(self):
        self.process.poll()  # Reap the launch parent before checking its group.
        try:
            os.killpg(self.process.pid, 0)
            return True
        except ProcessLookupError:
            return False

    def __exit__(self, exc_type, exc, traceback):
        print("正在关闭本次启动的雷达和重定位节点 ...", flush=True)
        previous = {sig: signal.signal(sig, signal.SIG_IGN)
                    for sig in (signal.SIGINT, signal.SIGTERM, signal.SIGHUP)}
        try:
            for sig, timeout in ((signal.SIGINT, 25.0), (signal.SIGTERM, 5.0),
                                 (signal.SIGKILL, 2.0)):
                try:
                    os.killpg(self.process.pid, sig)
                except ProcessLookupError:
                    break
                deadline = time.monotonic() + timeout
                while self._group_alive() and time.monotonic() < deadline:
                    time.sleep(0.1)
                if not self._group_alive():
                    break
            self.process.poll()
        finally:
            for sig, handler in previous.items():
                signal.signal(sig, handler)


def read_origin(path):
    if not path.exists():
        return None
    origins = [line.strip() for line in path.read_text().splitlines()
               if line.split() and line.split()[0] == "origin"]
    if len(origins) > 1:
        raise ValueError(f"{path} 有多个 origin，请先检查点位文件")
    if not origins:
        return None
    fields = origins[0].split()
    if len(fields) != 4 or not all(math.isfinite(float(v)) for v in fields[1:]):
        raise ValueError(f"{path} 的 origin 格式无效")
    return origins[0]


def write_targets(path, origin, targets, backup):
    lines = ([origin] if origin else []) + [
        f"target {x:.6f} {y:.6f} {yaw:.4f}" for x, y, yaw in targets
    ]
    temporary = None
    try:
        with tempfile.NamedTemporaryFile("w", dir=path.parent, prefix=".points-",
                                         delete=False) as stream:
            temporary = Path(stream.name)
            stream.write("\n".join(lines) + "\n")
            stream.flush()
            os.fsync(stream.fileno())
        if path.exists() and backup is not None and not backup.exists():
            shutil.copy2(path, backup)
        os.replace(temporary, path)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def relocated_pose(node, buffer):
    from rclpy.time import Time

    x, y, yaw, received = node.get_pose()
    age = time.monotonic() - received
    if received <= 0 or age < 0 or age > TF_MAX_AGE_SEC:
        raise RuntimeError(f"定位未更新（{age:.2f}s），不能打点")
    if not buffer.can_transform("map", "base_link", Time()):
        raise RuntimeError("map -> base_link TF 未连通，不能打点")
    if not buffer.can_transform("world", "imu", Time()):
        raise RuntimeError("world -> imu TF 缺失，不能打点")
    transform = buffer.lookup_transform("world", "imu", Time())
    stamp = transform.header.stamp
    source_ns = stamp.sec * 1_000_000_000 + stamp.nanosec
    age = (node.get_clock().now().nanoseconds - source_ns) / 1e9
    if source_ns <= 0 or age < -0.05 or age > TF_MAX_AGE_SEC:
        raise RuntimeError(f"重定位 TF 未更新（{age:.2f}s），不能打点")
    return x, y, math.degrees(yaw)


def record_targets(launch=None):
    import rclpy
    from nav_msgs.msg import Odometry
    from rclpy.executors import SingleThreadedExecutor
    from rclpy.node import Node
    from rclpy.signals import SignalHandlerOptions
    from tf2_ros import Buffer, TransformListener

    class Localizer(Node):
        def __init__(self):
            super().__init__("mid360_target_picker")
            self.pose = (0.0, 0.0, 0.0, 0.0)
            self.last_stamp = 0
            self.create_subscription(Odometry, "/lio/robo/odom", self.on_odom, 1)

        def on_odom(self, msg):
            if msg.header.frame_id != "world":
                return
            p = msg.pose.pose.position
            q = msg.pose.pose.orientation
            values = (p.x, p.y, q.x, q.y, q.z, q.w)
            if not all(math.isfinite(value) for value in values):
                return
            norm = math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w)
            if norm < 1e-6:
                return
            stamp = msg.header.stamp.sec * 1_000_000_000 + msg.header.stamp.nanosec
            source_age = (self.get_clock().now().nanoseconds - stamp) / 1e9
            if (stamp <= self.last_stamp or source_age < -0.05
                    or source_age > TF_MAX_AGE_SEC):
                return
            self.last_stamp = stamp
            qx, qy, qz, qw = (value / norm for value in (q.x, q.y, q.z, q.w))
            yaw = math.atan2(2 * (qw*qz + qx*qy), 1 - 2 * (qy*qy + qz*qz))
            self.pose = (float(p.x), float(p.y), yaw,
                         time.monotonic() - max(0.0, source_age))

        def get_pose(self):
            return self.pose

    origin = read_origin(POINTS_FILE)
    # Let Python unwind the context manager on Ctrl+C, termination or SSH hangup.
    rclpy.init(signal_handler_options=SignalHandlerOptions.NO)
    node = Localizer()
    buffer = Buffer()
    listener = TransformListener(buffer, node)
    executor = SingleThreadedExecutor()
    executor.add_node(node)

    def spin_once(timeout_sec):
        if launch is not None:
            launch.check_running()
        executor.spin_once(timeout_sec=timeout_sec)

    targets = []
    backup = None
    try:
        print("等待原地图重定位和新鲜定位 ...", flush=True)
        last_notice = 0.0
        while rclpy.ok():
            spin_once(timeout_sec=0.2)
            try:
                relocated_pose(node, buffer)
                break
            except RuntimeError:
                if time.monotonic() - last_notice >= 10.0:
                    print("仍在等待重定位；检查 nav.launch.py 的 ICP 和 TF 日志", flush=True)
                    last_notice = time.monotonic()
        else:
            return
        print("定位已就绪，等待 2 秒稳定 ...", flush=True)
        end = time.monotonic() + 2.0
        while time.monotonic() < end:
            spin_once(timeout_sec=0.1)
        x, y, yaw = relocated_pose(node, buffer)
        print(f"当前定位: x={x:.3f} y={y:.3f} yaw={yaw:.1f}°")
        print("移动到新目标位置后输入 g；l 查看本次目标；q 退出。每次 g 立即保存。")
        print("原 origin 保留；第一次 g 会备份并替换旧 target。")
        while rclpy.ok():
            try:
                command = input("g/l/q > ").strip().lower()
            except EOFError:
                command = "q"
            if command == "q":
                break
            if launch is not None:
                launch.check_running()
            if command == "l":
                for index, (x, y, yaw) in enumerate(targets, 1):
                    print(f"目标 #{index}: x={x:.3f} y={y:.3f} yaw={yaw:.1f}°")
                if not targets:
                    print("本次还没有打点；原 points.txt 未改变")
                continue
            if command != "g":
                print("请输入 g、l 或 q")
                continue
            try:
                # input() blocks the executor; let odometry and TF both refresh.
                refresh_until = time.monotonic() + 0.3
                while time.monotonic() < refresh_until:
                    spin_once(timeout_sec=0.05)
                pose = relocated_pose(node, buffer)
                candidate = targets + [pose]
                if backup is None and POINTS_FILE.exists():
                    stamp = datetime.now().strftime("%Y%m%d-%H%M%S-%f")
                    backup = POINTS_FILE.with_name(f"points.txt.bak-{stamp}")
                write_targets(POINTS_FILE, origin, candidate, backup)
                targets = candidate
                print(f"已保存目标 #{len(targets)}: x={pose[0]:.3f} "
                      f"y={pose[1]:.3f} yaw={pose[2]:.1f}°")
                if backup is not None and len(targets) == 1:
                    print(f"旧点位备份: {backup}")
            except (RuntimeError, OSError) as exc:
                print(f"未记录：{exc}")
    except KeyboardInterrupt:
        print("\n退出；已记录的目标已保存")
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.try_shutdown()


def main():
    parser = argparse.ArgumentParser(description="在原地图中重新记录目标点")
    parser.add_argument("--start-lidar", action="store_true",
                        help="同时启动雷达和原地图重定位，退出时一并关闭")
    args = parser.parse_args()

    def interrupted(signum, frame):
        raise KeyboardInterrupt

    previous = {sig: signal.signal(sig, interrupted)
                for sig in (signal.SIGTERM, signal.SIGHUP)}
    try:
        if args.start_lidar:
            with ManagedLaunch(POINTS_FILE.parent) as launch:
                record_targets(launch)
        else:
            record_targets()
        return 0
    except KeyboardInterrupt:
        return 130
    except (RuntimeError, OSError, ValueError) as exc:
        print(f"无法继续打点：{exc}")
        return 1
    finally:
        for sig, handler in previous.items():
            signal.signal(sig, handler)


if __name__ == "__main__":
    raise SystemExit(main())
