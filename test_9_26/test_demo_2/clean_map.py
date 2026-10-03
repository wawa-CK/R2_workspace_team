#!/usr/bin/env python3
"""清理 Super-LIO 地图 map.pcd 里坐标异常的坏点（防止 relocation_node 崩溃）。

用法：
    python3 clean_map.py

背景：建图时偶发产生坐标天文数字（如 -6e16）的坏点，会让 PCL 体素栅格
索引溢出，导致 relocation_node 段错误崩溃。本脚本过滤掉这些坏点。
"""
import re
import shutil
import struct

MAP_PCD = "/home/slam/r2_ws/lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd"
THRESHOLD = 100.0   # 坐标绝对值超过 100m 判定为坏点


def main():
    with open(MAP_PCD, "rb") as f:
        raw = f.read()

    idx = raw.find(b"DATA binary")
    if idx < 0:
        print("❌ map.pcd 不是 binary 格式")
        return
    header_end = raw.find(b"\n", idx) + 1
    header = raw[:header_end]
    data = raw[header_end:]

    ptsize = 16  # x y z intensity，4 个 float
    total = len(data) // ptsize
    good = bytearray()
    bad = 0
    for i in range(0, len(data), ptsize):
        x, y, z, _ = struct.unpack_from("ffff", data, i)
        if abs(x) > THRESHOLD or abs(y) > THRESHOLD or abs(z) > THRESHOLD:
            bad += 1
        else:
            good += data[i:i + ptsize]

    if bad == 0:
        print("✅ 没有坏点，无需清理")
        return

    good_count = len(good) // ptsize
    shutil.copy2(MAP_PCD, MAP_PCD + ".bak")

    new_header = re.sub(rb"WIDTH\s+\d+", b"WIDTH " + str(good_count).encode(), header)
    new_header = re.sub(rb"POINTS\s+\d+", b"POINTS " + str(good_count).encode(), new_header)

    with open(MAP_PCD, "wb") as f:
        f.write(new_header)
        f.write(good)

    print(f"✅ 清理完成：{total} → {good_count} 个点（删除 {bad} 个坏点）")
    print(f"   原图备份为 {MAP_PCD}.bak")


if __name__ == "__main__":
    main()
