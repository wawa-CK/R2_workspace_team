#!/usr/bin/env python3
"""Wait for fresh Super-LIO odometry and the complete navigation TF chain."""

import math
import time

import rclpy
from livox_ros_driver2.msg import CustomMsg
from nav_msgs.msg import Odometry
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from rclpy.time import Time
from sensor_msgs.msg import Imu
from tf2_ros import Buffer, TransformListener

MAX_DATA_AGE_SEC = 0.5
MAX_SENSOR_GAP_SEC = 2.0
READY_SAMPLES = 3


class RelocationCheck(Node):
    def __init__(self):
        super().__init__("wait_for_relocation")
        self.latest_odom_stamp = None
        self.last_lidar_received = None
        self.last_imu_received = None
        self.last_status = "尚未收到新鲜的 /lio/robo/odom"
        self.buffer = Buffer()
        self.listener = TransformListener(self.buffer, self)
        self.create_subscription(Odometry, "/lio/robo/odom", self.on_odom, 10)
        self.create_subscription(CustomMsg, "/livox/lidar", self.on_lidar,
                                 qos_profile_sensor_data)
        self.create_subscription(Imu, "/livox/imu", self.on_imu,
                                 qos_profile_sensor_data)

    def on_lidar(self, msg):
        if msg.point_num > 0:
            self.last_lidar_received = time.monotonic()

    def on_imu(self, _msg):
        self.last_imu_received = time.monotonic()

    def on_odom(self, msg):
        if msg.header.frame_id != "world":
            return
        p = msg.pose.pose.position
        q = msg.pose.pose.orientation
        if not all(math.isfinite(value) for value in (
                p.x, p.y, p.z, q.x, q.y, q.z, q.w)):
            return
        self.latest_odom_stamp = Time.from_msg(msg.header.stamp)

    def fresh(self, stamp):
        if stamp is None or stamp.nanoseconds == 0:
            return False
        age = (self.get_clock().now() - stamp).nanoseconds / 1e9
        return 0 <= age <= MAX_DATA_AGE_SEC

    def sensor_status(self):
        now = time.monotonic()
        lidar_ok = (self.last_lidar_received is not None and
                    now - self.last_lidar_received <= MAX_SENSOR_GAP_SEC)
        imu_ok = (self.last_imu_received is not None and
                  now - self.last_imu_received <= MAX_SENSOR_GAP_SEC)
        if not lidar_ok and not imu_ok:
            return "没有收到 /livox/lidar 和 /livox/imu；检查雷达供电、网线及驱动"
        if not lidar_ok:
            return "没有收到 /livox/lidar；检查雷达点云话题"
        if not imu_ok:
            return "没有收到 /livox/imu；检查雷达 IMU 话题"
        return "雷达和 IMU 都有数据，但尚无有效定位；查看 Global ICP 匹配日志"

    def tf_status(self):
        frames = (("map", "world"), ("world", "imu"), ("imu", "base_link"))
        return ", ".join(
            f"{parent}->{child}={'有' if self.buffer.can_transform(parent, child, Time()) else '无'}"
            for parent, child in frames)

    def ready(self):
        if not self.fresh(self.latest_odom_stamp):
            self.last_status = self.sensor_status()
            return False
        if not self.buffer.can_transform("world", "imu", Time()):
            self.last_status = "已有定位，但缺少 world -> imu TF；检查 relocation_node"
            return False
        transform = self.buffer.lookup_transform("world", "imu", Time())
        if not self.fresh(Time.from_msg(transform.header.stamp)):
            self.last_status = "world -> imu TF 已过期；检查重定位是否仍在运行"
            return False
        if not self.buffer.can_transform("map", "base_link", Time()):
            self.last_status = "动态定位已更新，但 map -> base_link 未连通；检查两段静态 TF"
            return False
        self.last_status = "定位与 map -> base_link TF 均已更新"
        return True


def main():
    rclpy.init()
    node = RelocationCheck()
    good_samples = 0
    last_notice = 0.0
    try:
        print("等待实时里程计及完整的 map -> base_link TF 链...", flush=True)
        while rclpy.ok():
            rclpy.spin_once(node, timeout_sec=0.2)
            good_samples = good_samples + 1 if node.ready() else 0
            if good_samples >= READY_SAMPLES:
                print("重定位就绪，启动 Nav2 规划器。", flush=True)
                return 0
            if time.monotonic() - last_notice >= 10.0:
                last_notice = time.monotonic()
                print(f"仍在等待重定位：{node.last_status}；TF：{node.tf_status()}。",
                      flush=True)
        print(f"重定位检查已停止：{node.last_status}；"
              f"TF：{node.tf_status()}；Nav2 不会启动。", flush=True)
        return 1
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == "__main__":
    raise SystemExit(main())
