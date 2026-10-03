#!/usr/bin/env python3
"""手动启动 nav.launch.py 后，按 g 回车记录原地图中的五个目标点。"""

import math
import os
from pathlib import Path
import shutil
import time
from datetime import datetime

import rclpy
from nav_msgs.msg import Odometry
from rclpy.node import Node

OUTPUT_FILE = Path(__file__).resolve().parent / "point.txt"
POINT_COUNT = 5


class PointRecorder(Node):
    def __init__(self):
        super().__init__("record_five_points")
        self.pose = None
        self.after_stamp = 0
        self.create_subscription(Odometry, "/lio/robo/odom", self.on_pose, 1)

    def on_pose(self, msg):
        stamp = msg.header.stamp.sec * 1_000_000_000 + msg.header.stamp.nanosec
        age = (self.get_clock().now().nanoseconds - stamp) / 1e9
        if msg.header.frame_id != "world" or stamp < self.after_stamp or not 0 <= age <= 0.5:
            return
        p, q = msg.pose.pose.position, msg.pose.pose.orientation
        values = (p.x, p.y, p.z, q.x, q.y, q.z, q.w)
        if not all(math.isfinite(value) for value in values):
            return
        norm = math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w)
        if norm < 1e-6:
            return
        qx, qy, qz, qw = (value / norm for value in (q.x, q.y, q.z, q.w))
        yaw = math.degrees(math.atan2(2*(qw*qz + qx*qy), 1 - 2*(qy*qy + qz*qz)))
        self.pose = (p.x, p.y, p.z, qx, qy, qz, qw, yaw)

    def capture(self):
        # 按 g 后取新发布的定位，避免 input 等待期间积压的旧消息。
        self.pose = None
        self.after_stamp = self.get_clock().now().nanoseconds
        deadline = time.monotonic() + 3.0
        while rclpy.ok() and self.pose is None and time.monotonic() < deadline:
            rclpy.spin_once(self, timeout_sec=0.1)
        return self.pose


def main():
    rclpy.init()
    node = PointRecorder()
    stream = None
    count = 0
    try:
        print("请先等待 nav.launch.py 重定位成功，再推车到目标位置并停稳。")
        print(f"按 g 回车记录，共 {POINT_COUNT} 个点；输出：{OUTPUT_FILE}")
        while rclpy.ok() and count < POINT_COUNT:
            command = input(f"第 {count + 1}/{POINT_COUNT} 个目标点，输入 g：").strip().lower()
            if command != "g":
                continue
            pose = node.capture()
            if pose is None:
                print("3 秒内未收到新鲜定位，本次未记录。请检查重定位，再按 g。")
                continue
            if stream is None:
                if OUTPUT_FILE.exists():
                    stamp = datetime.now().strftime("%Y%m%d-%H%M%S-%f")
                    backup = OUTPUT_FILE.with_name(f"point.txt.bak-{stamp}")
                    shutil.copy2(OUTPUT_FILE, backup)
                    print(f"旧文件已备份：{backup.name}")
                stream = OUTPUT_FILE.open("w", encoding="utf-8")
                stream.write("# frame: world；位置单位：米；yaw 单位：度\n")
                stream.write("# id x y z qx qy qz qw yaw_deg\n")
            stream.write(f"{count + 1} " + " ".join(f"{value:.8f}" for value in pose) + "\n")
            stream.flush()
            os.fsync(stream.fileno())
            count += 1
            print(f"已保存 #{count}：x={pose[0]:.3f} y={pose[1]:.3f} "
                  f"z={pose[2]:.3f} yaw={pose[7]:.1f}°")
        if count == POINT_COUNT:
            print(f"5 个目标点已全部保存：{OUTPUT_FILE}")
    except (KeyboardInterrupt, EOFError):
        print(f"\n已退出，已保存 {count} 个目标点。")
    finally:
        if stream is not None:
            stream.close()
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == "__main__":
    main()
