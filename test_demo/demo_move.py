#!/usr/bin/env python3
"""
R2 底盘移动 demo —— 通过 TCP 控制下位机。

用法：
    python3 demo_move.py

菜单：
    1. 前进 1 秒
    2. 左转 1 秒
    3. 右转 1 秒
    4. 后退 1 秒
    5. 急停
    0. 退出

说明：
    - 通过 TCP 连 192.168.2.199:5000，按 usc 的帧格式发 10 通道速度。
    - 前进/后退：发 ch2 速度（定时开环，持续 MOVE_TIME 秒）。
    - 左转/右转：发 des_yaw（目标航向）走航向 PID，yaw 固定 0 当假反馈，
      角速度 = 0.00059 * TURN_DES_YAW（rad/s）。方向反了就把左转/右转的 TURN_DES_YAW 正负号互换。
    - 每个动作都是定时开环，不追求精确距离/角度，改脚本顶部的 SPEED_*/TURN_RAD_S/MOVE_TIME 即可。
    - 移动期间会以 70Hz 持续发帧（下位机 500ms 收不到帧就自动停）。
    - 任何时候按 Ctrl+C 都会立即发零速帧急停。
"""

import socket
import struct
import time

# ==================== 网络配置 ====================
TCP_IP = "192.168.2.199"
TCP_PORT = 5000

# ==================== 帧常量（和 usc 上位机完全一致）====================
SOF1 = 0xA5
SOF2 = 0x5A
LEN = 0x1C        # payload 长度 = 28 字节（v3 格式）
TYPE = 0x01       # 帧类型：通道控制帧
FRAME_HZ = 70     # 发帧频率

# ==================== 移动参数（【方向反了就把正负号互换】）====================
# 前进/后退速度（ch2，满量程 ±600 对应 ±4 m/s）
SPEED_FORWARD = 400        # 前进速度
SPEED_BACKWARD = -400      # 后退速度
MOVE_TIME = 1.0            # 每个动作持续 1 秒

# ==================== 旋转参数 ====================
# 下位机 NET 模式忽略 ch3，旋转靠航向 PID：
#   角速度 = KP * (des_yaw - yaw) = 0.00059 * des_yaw   （yaw 固定发 0 当假反馈）
# 所以要 1 rad/s 旋转 → des_yaw = 1/0.00059 ≈ 1695
TURN_RAD_S = 1.0           # 目标旋转角速度（rad/s）
TURN_DES_YAW = int(TURN_RAD_S / 0.00059)   # 换算成 des_yaw（左转用正，右转用负）

# ==================== 通道定义 ====================
# ch0=横向  ch1=武器头升降  ch2=前进  ch3=旋转  ch4~ch9=功能(保持安全值1)
CHANNEL_COUNT = 10
SAFE_SWITCH = 1


def crc16_ccitt(data: bytes) -> int:
    """CRC16-CCITT (poly 0x1021, init 0xFFFF)，和下位机一致。"""
    crc = 0xFFFF
    for byte in data:
        crc ^= (byte << 8)
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


def build_frame(seq: int, channels: list, yaw: int = 0,
                des_yaw: int = 0, cylinder: int = 0) -> bytes:
    """按 usc 协议打包一帧：SOF1 SOF2 LEN TYPE + seq + 10通道 + yaw + 目标yaw + 气缸 + CRC。"""
    payload = struct.pack("<H", seq & 0xFFFF)
    for ch in channels:
        payload += struct.pack("<h", max(-32768, min(32767, int(ch))))
    payload += struct.pack("<h", yaw)
    payload += struct.pack("<h", des_yaw)
    payload += struct.pack("<h", cylinder)
    crc = crc16_ccitt(bytes([LEN, TYPE]) + payload)
    return bytes([SOF1, SOF2, LEN, TYPE]) + payload + struct.pack("<H", crc)


def motion_channels(lateral=0, forward=0, rotation=0) -> list:
    """构造底盘移动通道：ch0=横向 ch2=前进 ch3=旋转，ch4~ch9 保持安全值 1。"""
    ch = [0, 0, 0, 0] + [SAFE_SWITCH] * 6
    ch[0] = int(lateral)
    ch[2] = int(forward)
    ch[3] = int(rotation)
    return ch


class Sender:
    """TCP 发帧器：连下位机 + 持续发帧 + 停车。"""

    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(3.0)
        print(f"正在连接 {TCP_IP}:{TCP_PORT} ...")
        self.sock.connect((TCP_IP, TCP_PORT))
        self.sock.settimeout(None)
        self.seq = 0
        print("✅ 已连接下位机")

    def send(self, channels, yaw=0, des_yaw=0):
        frame = build_frame(self.seq, channels, yaw, des_yaw)
        self.sock.sendall(frame)
        self.seq = (self.seq + 1) & 0xFFFF

    def stop(self):
        """发零速帧停车。"""
        self.send(motion_channels(0, 0, 0))

    def move_for(self, forward, rotation, duration, name=""):
        """持续发速度 duration 秒，然后自动停车。"""
        ch = motion_channels(forward=forward, rotation=rotation)
        end = time.time() + duration
        print(f"执行：{name}（持续 {duration:.1f}s）...")
        while time.time() < end:
            self.send(ch)
            time.sleep(1.0 / FRAME_HZ)
        self.stop()
        print(f"完成：{name}，已停车")

    def rotate_for(self, des_yaw, duration, name=""):
        """用航向 PID 旋转：des_yaw 设目标航向（制造恒定角速度），yaw 固定 0 当假反馈。"""
        ch = motion_channels(0, 0, 0)   # 无平移
        end = time.time() + duration
        print(f"执行：{name}（持续 {duration:.1f}s）...")
        while time.time() < end:
            self.send(ch, yaw=0, des_yaw=des_yaw)
            time.sleep(1.0 / FRAME_HZ)
        self.stop()
        print(f"完成：{name}，已停车")

    def close(self):
        try:
            self.stop()
        except Exception:
            pass
        try:
            self.sock.close()
        except Exception:
            pass


def main():
    sender = None
    try:
        sender = Sender()
        sender.stop()  # 启动先发一帧零速，确保停在原地

        while True:
            print("\n" + "-" * 40)
            print("R2 底盘移动 demo")
            print("  1. 前进 1 秒")
            print("  2. 左转 1 秒")
            print("  3. 右转 1 秒")
            print("  4. 后退 1 秒")
            print("  5. 急停")
            print("  0. 退出")
            print("-" * 40)

            try:
                choice = input("请输入选项：").strip()
            except (EOFError, KeyboardInterrupt):
                break

            if choice == "1":
                sender.move_for(SPEED_FORWARD, 0, MOVE_TIME, "前进 1 秒")
            elif choice == "2":
                sender.rotate_for(TURN_DES_YAW, MOVE_TIME, "左转 1 秒")
            elif choice == "3":
                sender.rotate_for(-TURN_DES_YAW, MOVE_TIME, "右转 1 秒")
            elif choice == "4":
                sender.move_for(SPEED_BACKWARD, 0, MOVE_TIME, "后退 1 秒")
            elif choice == "5":
                sender.stop()
                print("🛑 急停，已发零速帧")
            elif choice == "0":
                print("退出")
                break
            else:
                print("无效输入，请输入 0-5")

    except KeyboardInterrupt:
        print("\n🛑 Ctrl+C 急停")
    except Exception as e:
        print(f"❌ 出错：{e}")
    finally:
        if sender is not None:
            try:
                sender.stop()
            except Exception:
                pass
            sender.close()
        print("已安全退出")


if __name__ == "__main__":
    main()
