#!/usr/bin/env python3
"""
手动控制 R2 移动 —— 键盘 WSAD 控制。

用法：
    python3 hand.py

按键：
    w = 前进    s = 后退    a = 左转    d = 右转
    q = 退出    （松开方向键约 0.3 秒后自动停车）

说明：
    - 前进/后退：发 ch2 速度
    - 左转/右转：发 des_yaw（航向 PID），因为下位机 NET 模式忽略 ch3
    - 按住方向键持续走，松开后自动停车
    - 以 70Hz 稳定发帧（用超时判断"松开"，不依赖按键重复率，避免一抖一抖）
    - 方向反了就把 SPEED 或 TURN_DES_YAW 的正负号互换
"""

import select
import socket
import struct
import sys
import termios
import time
import tty

# ==================== 网络 / 帧常量（和 usc 一致）====================
TCP_IP = "192.168.2.199"
TCP_PORT = 5000
SOF1 = 0xA5
SOF2 = 0x5A
LEN = 0x1C
TYPE = 0x01
SAFE_SWITCH = 1
FRAME_HZ = 70

# ==================== 移动参数 ====================
SPEED_FORWARD = 270       # 前进/后退速度（ch2，满量程 ±600 = ±4 m/s）→ 600×0.45
TURN_RAD_S = 0.5          # 旋转角速度（rad/s）
TURN_DES_YAW = int(TURN_RAD_S / 0.00059)   # 换算成 des_yaw（下位机 KP=0.00059）


def crc16_ccitt(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= (byte << 8)
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
    return crc


def build_frame(seq, channels, yaw=0, des_yaw=0, cylinder=0):
    payload = struct.pack("<H", seq & 0xFFFF)
    for ch in channels:
        payload += struct.pack("<h", max(-32768, min(32767, int(ch))))
    payload += struct.pack("<h", yaw)
    payload += struct.pack("<h", des_yaw)
    payload += struct.pack("<h", cylinder)
    crc = crc16_ccitt(bytes([LEN, TYPE]) + payload)
    return bytes([SOF1, SOF2, LEN, TYPE]) + payload + struct.pack("<H", crc)


def motion_channels(lateral=0, forward=0, rotation=0):
    ch = [0, 0, 0, 0] + [SAFE_SWITCH] * 6
    ch[0] = int(lateral)
    ch[2] = int(forward)
    ch[3] = int(rotation)
    return ch


class Sender:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.settimeout(3.0)
        self.sock.connect((TCP_IP, TCP_PORT))
        self.sock.settimeout(None)
        self.seq = 0
        print(f"✅ 已连接下位机 {TCP_IP}:{TCP_PORT}")

    def send(self, channels, yaw=0, des_yaw=0):
        self.sock.sendall(build_frame(self.seq, channels, yaw, des_yaw))
        self.seq = (self.seq + 1) & 0xFFFF

    def stop(self):
        self.send(motion_channels(0, 0, 0), yaw=0, des_yaw=0)

    def close(self):
        try:
            self.stop()
        except Exception:
            pass
        try:
            self.sock.close()
        except Exception:
            pass


def get_key():
    """非阻塞读一个按键，没按键返回 None。"""
    if select.select([sys.stdin], [], [], 0)[0]:
        return sys.stdin.read(1)
    return None


def main():
    sender = None
    old_settings = None
    try:
        sender = Sender()
        sender.stop()

        # 设置终端为 cbreak（字符立即读取，无回显）
        old_settings = termios.tcgetattr(sys.stdin)
        tty.setcbreak(sys.stdin.fileno())

        print("\n" + "=" * 45)
        print("手动控制模式")
        print("  w=前进  s=后退  a=左转  d=右转  q=退出")
        print("  按住方向键持续走，松开自动停")
        print("=" * 45)

        direction = None            # 当前运动方向：None/"fwd"/"back"/"left"/"right"
        last_key_time = time.time() # 上次收到方向键的时间
        RELEASE_TIMEOUT = 0.3       # 松开方向键 0.3 秒后判定停车（可调）

        running = True
        while running:
            # 读空输入缓冲，处理所有按键
            while True:
                key = get_key()
                if key is None:
                    break
                if key == "w":
                    direction = "fwd"; last_key_time = time.time()
                elif key == "s":
                    direction = "back"; last_key_time = time.time()
                elif key == "a":
                    direction = "left"; last_key_time = time.time()
                elif key == "d":
                    direction = "right"; last_key_time = time.time()
                elif key == "q":
                    running = False
                    break
                # 其他键忽略，保持当前方向

            # 松开检测：超过超时时间没收到新方向键 → 停车
            if direction is not None and (time.time() - last_key_time) > RELEASE_TIMEOUT:
                direction = None

            # 按当前方向持续发帧（稳定 70Hz，不会一抖一抖）
            if direction == "fwd":
                sender.send(motion_channels(forward=SPEED_FORWARD))
            elif direction == "back":
                sender.send(motion_channels(forward=-SPEED_FORWARD))
            elif direction == "left":
                # 左转：航向 PID（des_yaw 正 + yaw=0 假反馈）
                sender.send(motion_channels(0, 0, 0), yaw=0, des_yaw=TURN_DES_YAW)
            elif direction == "right":
                # 右转：航向 PID（des_yaw 负 + yaw=0 假反馈）
                sender.send(motion_channels(0, 0, 0), yaw=0, des_yaw=-TURN_DES_YAW)
            else:
                sender.send(motion_channels(0, 0, 0), yaw=0, des_yaw=0)

            time.sleep(1.0 / FRAME_HZ)

    except KeyboardInterrupt:
        print("\n🛑 Ctrl+C 退出")
    except Exception as e:
        print(f"❌ 出错：{e}")
    finally:
        if old_settings is not None:
            termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)
        if sender is not None:
            sender.close()
        print("已安全退出")


if __name__ == "__main__":
    main()
