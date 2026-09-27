#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
pcd_downsample.py - PCD点云降采样工具

用法：
    python3 pcd_downsample.py input.pcd output.pcd -v 0.1 --z-min -0.5 --z-max 2.0 --binary
"""
import sys
import os
import argparse
import struct
import numpy as np
from typing import List, Tuple


def read_pcd_ascii(file_path: str) -> np.ndarray:
    """读取ASCII格式的PCD文件"""
    points = []
    in_data = False

    with open(file_path, 'r') as f:
        for line in f:
            line = line.strip()
            if line == 'DATA ascii':
                in_data = True
                continue
            if in_data and line:
                parts = line.split()
                if len(parts) >= 3:
                    try:
                        x, y, z = float(parts[0]), float(parts[1]), float(parts[2])
                        points.append([x, y, z])
                    except ValueError:
                        continue

    return np.array(points) if points else np.empty((0, 3))


def voxel_downsample(points: np.ndarray, voxel_size: float) -> np.ndarray:
    """体素降采样"""
    if len(points) == 0:
        return points

    # 计算体素索引
    voxel_indices = np.floor(points / voxel_size).astype(np.int32)

    # 使用字典去重
    voxel_dict = {}
    for i, idx in enumerate(voxel_indices):
        key = tuple(idx)
        if key not in voxel_dict:
            voxel_dict[key] = []
        voxel_dict[key].append(points[i])

    # 取每个体素的中心点
    downsampled = []
    for voxel_points in voxel_dict.values():
        center = np.mean(voxel_points, axis=0)
        downsampled.append(center)

    return np.array(downsampled)


def filter_height(points: np.ndarray, z_min: float, z_max: float) -> np.ndarray:
    """高度过滤"""
    mask = (points[:, 2] >= z_min) & (points[:, 2] <= z_max)
    return points[mask]


def save_pcd_ascii(points: np.ndarray, file_path: str):
    """保存为ASCII PCD"""
    with open(file_path, 'w') as f:
        f.write("# .PCD v0.7 - Point Cloud Data file format\n")
        f.write("VERSION 0.7\n")
        f.write("FIELDS x y z\n")
        f.write("SIZE 4 4 4\n")
        f.write("TYPE F F F\n")
        f.write("COUNT 1 1 1\n")
        f.write(f"WIDTH {len(points)}\n")
        f.write("HEIGHT 1\n")
        f.write("VIEWPOINT 0 0 0 1 0 0 0\n")
        f.write(f"POINTS {len(points)}\n")
        f.write("DATA ascii\n")
        for pt in points:
            f.write(f"{pt[0]:.6f} {pt[1]:.6f} {pt[2]:.6f}\n")


def save_pcd_binary(points: np.ndarray, file_path: str):
    """保存为二进制PCD"""
    with open(file_path, 'wb') as f:
        header = (
            "# .PCD v0.7 - Point Cloud Data file format\n"
            "VERSION 0.7\n"
            "FIELDS x y z\n"
            "SIZE 4 4 4\n"
            "TYPE F F F\n"
            "COUNT 1 1 1\n"
            f"WIDTH {len(points)}\n"
            "HEIGHT 1\n"
            "VIEWPOINT 0 0 0 1 0 0 0\n"
            f"POINTS {len(points)}\n"
            "DATA binary\n"
        )
        f.write(header.encode('ascii'))
        points.astype(np.float32).tofile(f)


def main():
    parser = argparse.ArgumentParser(
        description='PCD点云降采样工具',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 体素降采样 (10cm) + 高度过滤
  python3 pcd_downsample.py input.pcd output.pcd -v 0.1 --z-min -0.5 --z-max 2.0

  # 保存为二进制格式
  python3 pcd_downsample.py input.pcd output.pcd -v 0.1 --binary
        """
    )

    parser.add_argument('input', help='输入PCD文件')
    parser.add_argument('output', help='输出PCD文件')
    parser.add_argument('-v', '--voxel-size', type=float, default=0.05,
                       help='体素大小(米)，默认0.05')
    parser.add_argument('--z-min', type=float, default=-float('inf'),
                       help='最小高度(米)')
    parser.add_argument('--z-max', type=float, default=float('inf'),
                       help='最大高度(米)')
    parser.add_argument('--binary', action='store_true',
                       help='保存为二进制格式')

    args = parser.parse_args()

    if not os.path.exists(args.input):
        print(f"❌ 文件不存在: {args.input}")
        sys.exit(1)

    print(f"读取: {args.input}")
    points = read_pcd_ascii(args.input)
    print(f"  原始点数: {len(points):,}")

    if len(points) == 0:
        print("❌ 没有读取到点云数据")
        sys.exit(1)

    # 高度过滤
    if args.z_min > -float('inf') or args.z_max < float('inf'):
        points = filter_height(points, args.z_min, args.z_max)
        print(f"  高度过滤后: {len(points):,} (z ∈ [{args.z_min}, {args.z_max}])")

    # 体素降采样
    print(f"  体素降采样: {args.voxel_size}m ...")
    points = voxel_downsample(points, args.voxel_size)
    print(f"  降采样后: {len(points):,}")

    # 保存
    os.makedirs(os.path.dirname(os.path.abspath(args.output)), exist_ok=True)
    if args.binary:
        save_pcd_binary(points, args.output)
        print(f"✅ 已保存(二进制): {args.output}")
    else:
        save_pcd_ascii(points, args.output)
        print(f"✅ 已保存(ASCII): {args.output}")

    size_mb = os.path.getsize(args.output) / (1024 * 1024)
    print(f"  文件大小: {size_mb:.2f} MB")


if __name__ == '__main__':
    main()
