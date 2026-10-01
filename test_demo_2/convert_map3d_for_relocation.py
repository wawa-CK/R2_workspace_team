#!/usr/bin/env python3
"""Convert test_demo/map3d.pcd (XYZ ASCII) to Super-LIO-compatible binary XYZI PCD.

This never overwrites the native relocation map. The output is a separate file.
"""
import argparse
import math
import struct
from pathlib import Path


def convert(source, destination):
    points = []
    data = False
    with source.open(encoding="ascii") as stream:
        for raw in stream:
            line = raw.strip()
            if not line:
                continue
            if data:
                fields = line.split()
                if len(fields) < 3:
                    continue
                xyz = tuple(float(value) for value in fields[:3])
                if all(math.isfinite(value) for value in xyz):
                    points.append(xyz)
            elif line.upper().startswith("DATA "):
                if line.split(maxsplit=1)[1].lower() != "ascii":
                    raise ValueError("输入必须是 ASCII PCD")
                data = True
    if not points:
        raise ValueError("输入没有有效 XYZ 点")
    destination.parent.mkdir(parents=True, exist_ok=True)
    header = ("# .PCD v0.7 - Point Cloud Data file format\n"
              "VERSION 0.7\n"
              "FIELDS x y z intensity\n"
              "SIZE 4 4 4 4\n"
              "TYPE F F F F\n"
              "COUNT 1 1 1 1\n"
              f"WIDTH {len(points)}\nHEIGHT 1\n"
              "VIEWPOINT 0 0 0 1 0 0 0\n"
              f"POINTS {len(points)}\nDATA binary\n").encode("ascii")
    with destination.open("wb") as stream:
        stream.write(header)
        for x, y, z in points:
            stream.write(struct.pack("<ffff", x, y, z, 0.0))
    return len(points)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path,
                        default=Path(__file__).with_name("map3d.pcd"), nargs="?")
    parser.add_argument("destination", type=Path,
                        default=Path(__file__).parent.parent / "lidar_ws/src/Super-LIO/src/super_lio/map/map3d_relocation_xyzi.pcd", nargs="?")
    args = parser.parse_args()
    count = convert(args.source, args.destination)
    print(f"已生成 {args.destination}：{count} 点，未修改原 map.pcd")


if __name__ == "__main__":
    main()
