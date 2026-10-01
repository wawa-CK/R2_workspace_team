import os

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # ① 雷达驱动（发布 /livox/lidar + /livox/imu）
    driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("livox_ros_driver2"), "/launch_ROS2/msg_MID360_launch.py"
        ]),
    )

    # 建图模式明确保存地图，rviz 由建图脚本单独启动。
    super_lio = Node(
        package="super_lio",
        executable="super_lio_node",
        name="super_lio_node",
        output="screen",
        parameters=[
            PathJoinSubstitution([FindPackageShare("super_lio"), "config", "livox_360.yaml"]),
            {"lio.map.save_map": True},
        ],
        arguments=["--ros-args", "--log-level", "info"],
    )

    return LaunchDescription([driver, super_lio])
