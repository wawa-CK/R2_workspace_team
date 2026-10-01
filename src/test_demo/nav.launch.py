import os

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

PKG_DIR = os.path.dirname(os.path.abspath(__file__))
LIO_CONFIG = os.path.join(
    os.path.dirname(PKG_DIR),
    "lidar_ws/src/Super-LIO/src/super_lio/config/livox_360.yaml",
)
RELOCATION_CONFIG = os.path.join(PKG_DIR, "relocation_params.yaml")
MAP_PCD = os.path.join(os.path.dirname(PKG_DIR),
                       "lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd")


def generate_launch_description():
    pkg_dir = PKG_DIR

    for path in (LIO_CONFIG, RELOCATION_CONFIG, MAP_PCD,
                 os.path.join(pkg_dir, "map2d.yaml")):
        if not os.path.isfile(path):
            raise RuntimeError(f"导航所需文件不存在：{path}")
    print(f"重定位地图（要求 Super-LIO 在当前路径编译）：{MAP_PCD}")
    print(f"重定位覆盖参数：{RELOCATION_CONFIG}")

    # ① 雷达驱动（发布 /livox/lidar + /livox/imu）
    driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("livox_ros_driver2"), "/launch_ROS2/msg_MID360_launch.py"
        ]),
    )

    # 保留建图时的外参，只覆盖重定位需要的参数，避免切换另一份配置改变坐标。
    super_lio = Node(
        package="super_lio",
        executable="relocation_node",
        name="relocation_node",
        output="screen",
        parameters=[LIO_CONFIG, RELOCATION_CONFIG],
        arguments=["--ros-args", "--log-level", "info"],
    )

    # ③ Nav2（map_server 加载地图 + planner 绕障规划 + TF 桥 + lifecycle）
    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_dir, "nav2_bringup.launch.py")),
    )

    return LaunchDescription([driver, super_lio, nav2])
