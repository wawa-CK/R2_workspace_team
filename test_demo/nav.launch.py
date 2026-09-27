import os
import re
import shutil
import struct

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare

MAP_PCD = "/home/slam/r2_ws/lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd"
THRESHOLD = 100.0   # 坐标绝对值超过 100m 判定为坏点


def clean_map_pcd():
    """清理 map.pcd 里坐标异常的坏点（防止 relocation_node 段错误崩溃）。"""
    try:
        with open(MAP_PCD, "rb") as f:
            raw = f.read()
    except FileNotFoundError:
        print("⚠️ map.pcd 不存在，跳过清理")
        return

    idx = raw.find(b"DATA binary")
    if idx < 0:
        print("⚠️ map.pcd 不是 binary 格式，跳过清理")
        return
    header_end = raw.find(b"\n", idx) + 1
    header = raw[:header_end]
    data = raw[header_end:]

    ptsize = 16  # x y z intensity，4 个 float
    good = bytearray()
    bad = 0
    for i in range(0, len(data), ptsize):
        x, y, z, _ = struct.unpack_from("ffff", data, i)
        if abs(x) > THRESHOLD or abs(y) > THRESHOLD or abs(z) > THRESHOLD:
            bad += 1
        else:
            good += data[i:i + ptsize]

    if bad == 0:
        print("✅ map.pcd 无坏点")
        return

    good_count = len(good) // ptsize
    shutil.copy2(MAP_PCD, MAP_PCD + ".bak")
    new_header = re.sub(rb"WIDTH\s+\d+", b"WIDTH " + str(good_count).encode(), header)
    new_header = re.sub(rb"POINTS\s+\d+", b"POINTS " + str(good_count).encode(), new_header)
    with open(MAP_PCD, "wb") as f:
        f.write(new_header)
        f.write(good)
    print(f"✅ 已自动清理 map.pcd：删除 {bad} 个坏点")


def generate_launch_description():
    pkg_dir = "/home/slam/r2_ws/test_demo"

    # 启动 relocation 前先自动清理地图坏点（防止 relocation 崩溃）
    clean_map_pcd()

    # ① 雷达驱动（发布 /livox/lidar + /livox/imu）
    driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("livox_ros_driver2"), "/launch_ROS2/msg_MID360_launch.py"
        ]),
    )

    # ② Super-LIO 重定位（发布 world→imu TF + /lio/robo/odom，关掉自带 rviz）
    super_lio = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("super_lio"), "/launch/relocation.py"
        ]),
        launch_arguments=[("rviz", "false")],
    )

    # ③ Nav2（map_server 加载地图 + planner 绕障规划 + TF 桥 + lifecycle）
    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_dir, "nav2_bringup.launch.py")),
    )

    return LaunchDescription([driver, super_lio, nav2])
