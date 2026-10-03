#!/usr/bin/env bash
# One terminal: source ROS, start relocation on the saved map, and record targets.
set -eo pipefail

PICK_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PICK_WS="$(dirname -- "$PICK_DIR")"
for setup_file in /opt/ros/humble/setup.bash "$PICK_WS/lidar_ws/install/setup.bash"; do
    if [[ ! -f "$setup_file" ]]; then
        echo "找不到 ROS 环境文件：$setup_file；请在小电脑运行本脚本。" >&2
        exit 1
    fi
    source "$setup_file"
done

exec python3 "$PICK_DIR/pick_targets.py" --start-lidar
