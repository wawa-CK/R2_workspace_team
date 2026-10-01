import os

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # ① 雷达驱动（发布 /livox/lidar + /livox/imu）
    driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("livox_ros_driver2"), "/launch_ROS2/msg_MID360_launch.py"
        ]),
    )

    # ② Super-LIO 建图（关掉自带 rviz，用建图脚本弹的 rviz）
    super_lio = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("super_lio"), "/launch/Livox_mid360.py"
        ]),
        launch_arguments=[("rviz", "false")],
    )

    return LaunchDescription([driver, super_lio])
