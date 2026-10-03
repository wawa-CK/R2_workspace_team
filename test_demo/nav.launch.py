import hashlib
import math
import os
import sys

from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, ExecuteProcess, GroupAction,
                            IncludeLaunchDescription, LogInfo, RegisterEventHandler)
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

PKG_DIR = os.path.dirname(os.path.abspath(__file__))
MAP_PCD = os.path.join(PKG_DIR, "map3d.pcd")
# Super-LIO prepends its compile-time source directory to save_map_dir.
SUPER_LIO_ROOT = os.path.join(os.path.dirname(PKG_DIR),
                              "lidar_ws/src/Super-LIO/src/super_lio")
RELOCATION_MAP_DIR = os.path.relpath(PKG_DIR, SUPER_LIO_ROOT)
MAP_COORD_LIMIT = 100.0
CONFLICTING_EXECUTABLES = {
    "livox_ros_driver2_node", "super_lio_node", "relocation_node",
    "planner_server", "map_server", "static_transform_publisher",
}


def find_conflicting_processes():
    conflicts = []
    for entry in os.scandir("/proc"):
        if not entry.name.isdigit() or int(entry.name) == os.getpid():
            continue
        try:
            executable = os.path.basename(os.readlink(f"{entry.path}/exe"))
        except (FileNotFoundError, PermissionError, OSError):
            continue
        if executable in CONFLICTING_EXECUTABLES:
            conflicts.append((int(entry.name), executable))
    return sorted(conflicts)


def report_map_pcd():
    """Record the exact 3D map used for relocation without changing it."""
    try:
        with open(MAP_PCD, "rb") as f:
            header = {}
            for line in f:
                parts = line.split()
                if parts:
                    header[parts[0]] = parts[1:]
                if parts and parts[0] == b"DATA":
                    break
            else:
                raise RuntimeError(f"地图 PCD 缺少 DATA 头：{MAP_PCD}")
            expected_layout = {
                b"FIELDS": [b"x", b"y", b"z"],
                b"SIZE": [b"4"] * 3,
                b"TYPE": [b"F"] * 3,
                b"COUNT": [b"1"] * 3,
                b"DATA": [b"ascii"],
            }
            if any(header.get(key) != value for key, value in expected_layout.items()):
                raise RuntimeError(f"地图 PCD 格式不是预期的 ASCII XYZ：{MAP_PCD}")
            try:
                point_count = int(header[b"POINTS"][0])
            except (KeyError, IndexError, ValueError):
                raise RuntimeError(f"地图 PCD 点数无效：{MAP_PCD}") from None
            if point_count <= 0:
                raise RuntimeError(f"地图 PCD 点数无效：{MAP_PCD}")
            observed = 0
            for line in f:
                fields = line.split()
                if len(fields) != 3:
                    raise RuntimeError(f"地图 PCD 第 {observed + 1} 个点不是 XYZ：{MAP_PCD}")
                try:
                    xyz = tuple(float(value) for value in fields)
                except ValueError:
                    raise RuntimeError(f"地图 PCD 第 {observed + 1} 个点含非法坐标：{MAP_PCD}") from None
                if not all(math.isfinite(value) and abs(value) <= MAP_COORD_LIMIT for value in xyz):
                    raise RuntimeError(
                        f"地图 PCD 第 {observed + 1} 个点无效或超出 ±{MAP_COORD_LIMIT:g}m："
                        f"{MAP_PCD}")
                observed += 1
            if observed != point_count:
                raise RuntimeError(
                    f"地图 PCD 点数不符：头部={point_count}，实际={observed}：{MAP_PCD}")
            f.seek(0)
            digest = hashlib.sha256()
            for chunk in iter(lambda: f.read(1024 * 1024), b""):
                digest.update(chunk)
    except FileNotFoundError:
        raise RuntimeError(f"三维地图不存在：{MAP_PCD}") from None
    print(f"三维地图：{MAP_PCD}；点数={point_count}；SHA256={digest.hexdigest()}",
          flush=True)


def generate_launch_description():
    pkg_dir = PKG_DIR

    conflicts = find_conflicting_processes()
    if conflicts:
        details = ", ".join(f"PID {pid} {name}" for pid, name in conflicts)
        raise RuntimeError(
            f"检测到已运行的雷达/建图/导航进程：{details}。"
            "请先关闭旧的 launch，确认进程退出后再启动导航。")

    report_map_pcd()

    # ① 雷达驱动（发布 /livox/lidar + /livox/imu）
    driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            FindPackageShare("livox_ros_driver2"), "/launch_ROS2/msg_MID360_launch.py"
        ]),
    )

    # 重定位只读已有地图，避免共用 YAML 的建图开关影响导航模式。
    super_lio = Node(
        package="super_lio",
        executable="relocation_node",
        name="relocation_node",
        output="screen",
        parameters=[
            PathJoinSubstitution([FindPackageShare("super_lio"), "config", "livox_360.yaml"]),
            {"lio.map.save_map": False,
             "lio.map.save_map_dir": RELOCATION_MAP_DIR,
             "lio.map.map_name": "map3d.pcd",
             "lio.relocation.update_map": False},
        ],
        arguments=["--ros-args", "--log-level", "info"],
    )

    # 先发布两段静态 TF，等待节点随后核对完整的 map -> base_link 链。
    tf_map_world = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["--frame-id", "map", "--child-frame-id", "world"],
        name="tf_map_world",
    )
    tf_imu_base = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["--frame-id", "imu", "--child-frame-id", "base_link"],
        name="tf_imu_base",
    )

    # 重定位匹配成功前不启动 Nav2；失败时保留驱动与重定位日志供排查。
    wait_for_relocation = ExecuteProcess(
        cmd=[sys.executable, os.path.join(pkg_dir, "wait_for_relocation.py")],
        name="wait_for_relocation",
        output="screen",
    )

    # ③ Nav2（map_server 加载地图 + planner 绕障规划 + lifecycle）
    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_dir, "nav2_bringup.launch.py")),
    )

    def on_relocation_check_exit(event, context):
        if event.returncode == 0:
            return [nav2]
        return [LogInfo(msg="重定位未就绪，Nav2 未启动。请检查上方 ICP 匹配日志和雷达数据。")]

    return LaunchDescription([
        DeclareLaunchArgument("start_nav2", default_value="true",
                              description="Start Nav2 after relocation; false for target picking."),
        driver,
        super_lio,
        tf_map_world,
        tf_imu_base,
        GroupAction([
            RegisterEventHandler(OnProcessExit(
                target_action=wait_for_relocation,
                on_exit=on_relocation_check_exit,
            )),
            wait_for_relocation,
        ], condition=IfCondition(LaunchConfiguration("start_nav2"))),
    ])
