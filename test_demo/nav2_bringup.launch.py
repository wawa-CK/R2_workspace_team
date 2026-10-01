import os

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    pkg_dir = os.path.dirname(os.path.abspath(__file__))
    params_file = os.path.join(pkg_dir, "nav2_params.yaml")
    map_yaml = os.path.join(pkg_dir, "map2d.yaml")

    # 2D 栅格地图服务器（加载 map2d.yaml -> /map）
    map_server = Node(
        package="nav2_map_server",
        executable="map_server",
        parameters=[{"yaml_filename": map_yaml}],
        name="map_server",
    )

    # 全局路径规划器（/compute_path_to_pose 动作，绕障规划）
    planner_server = Node(
        package="nav2_planner",
        executable="planner_server",
        parameters=[params_file],
        name="planner_server",
    )

    # lifecycle 管理器（激活 map_server + planner_server，否则它们停在 unconfigured）
    lifecycle_manager = Node(
        package="nav2_lifecycle_manager",
        executable="lifecycle_manager",
        name="lifecycle_manager_navigation",
        parameters=[{
            "autostart": True,
            "node_names": ["map_server", "planner_server"],
        }],
    )

    return LaunchDescription([
        map_server,
        planner_server,
        lifecycle_manager,
    ])
