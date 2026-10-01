import hashlib
import math
import os
import struct
import sys

from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription, LogInfo, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution

PKG_DIR = os.path.dirname(os.path.abspath(__file__))
MAP_PCD = os.path.join(os.path.dirname(PKG_DIR),
                       "lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd")
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
                b"FIELDS": [b"x", b"y", b"z", b"intensity"],
                b"SIZE": [b"4"] * 4,
                b"TYPE": [b"F"] * 4,
                b"COUNT": [b"1"] * 4,
                b"DATA": [b"binary"],
            }
            if any(header.get(key) != value for key, value in expected_layout.items()):
                raise RuntimeError(f"地图 PCD 格式不是预期的 binary XYZ intensity：{MAP_PCD}")
            try:
                point_count = int(header[b"POINTS"][0])
            except (KeyError, IndexError, ValueError):
                raise RuntimeError(f"地图 PCD 点数无效：{MAP_PCD}") from None
            if point_count <= 0:
                raise RuntimeError(f"地图 PCD 点数无效：{MAP_PCD}")
            payload_start = f.tell()
            payload_size = os.fstat(f.fileno()).st_size - payload_start
            if payload_size != point_count * 16:
                raise RuntimeError(f"地图 PCD 数据长度与 {point_count} 个点不符：{MAP_PCD}")
            invalid = 0
            for chunk in iter(lambda: f.read(1024 * 1024), b""):
                for x, y, z, _ in struct.iter_unpack("<ffff", chunk):
                    if not all(math.isfinite(value) and abs(value) <= MAP_COORD_LIMIT
                               for value in (x, y, z)):
                        invalid += 1
            if invalid:
                raise RuntimeError(
                    f"地图 PCD 有 {invalid} 个无效或超出 ±{MAP_COORD_LIMIT:g}m 的点："
                    f"{MAP_PCD}；原文件未改，请先核对地图")
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
            {"lio.map.save_map": False, "lio.relocation.update_map": False},
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
        driver,
        super_lio,
        tf_map_world,
        tf_imu_base,
        RegisterEventHandler(OnProcessExit(
            target_action=wait_for_relocation,
            on_exit=on_relocation_check_exit,
        )),
        wait_for_relocation,
    ])
