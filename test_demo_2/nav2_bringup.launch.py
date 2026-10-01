import os

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    pkg_dir = os.path.dirname(os.path.abspath(__file__))
    params_file = os.path.join(pkg_dir, "nav2_params.yaml")
    map_yaml = os.path.join(
        pkg_dir, "maps", "map2d.yaml"
        if os.environ.get("USE_LEGACY_MAP2D") == "1" else "../map2d.yaml"
    )
    map_yaml = os.path.normpath(map_yaml)
    planner_overrides = {}
    if os.environ.get("DISABLE_DYNAMIC_OBSTACLES") == "1":
        planner_overrides[
            "global_costmap.global_costmap.obstacle_layer.enabled"
        ] = False

    # TF 桥 1：map -> world（map2d 的 origin 就是 world 坐标，两者同系，恒等）
    tf_map_world = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["--frame-id", "map", "--child-frame-id", "world"],
        name="tf_map_world",
    )

    # TF 桥 2：imu -> base_link（近似恒等，实际有外参时可改这里）
    tf_imu_base = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["--frame-id", "imu", "--child-frame-id", "base_link"],
        name="tf_imu_base",
    )

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
        parameters=[params_file, planner_overrides],
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
        tf_map_world,
        tf_imu_base,
        map_server,
        planner_server,
        lifecycle_manager,
    ])
