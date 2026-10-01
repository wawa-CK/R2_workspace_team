#!/usr/bin/env python3
"""无硬件回归：模拟底盘、规划失败、定位断流及真实 ROS executor/action。

source /opt/ros/<发行版>/setup.bash 后，使用系统 Python 运行本文件。
测试不创建 TCP Sender；真实 ROS 测试使用独立 action 名，不启动雷达/底盘。
"""
import contextlib
from concurrent.futures import Future
import io
import math
import os
from pathlib import Path
import struct
import tempfile
import threading
import time
from types import SimpleNamespace
import unittest
from unittest.mock import Mock, patch
import uuid

import nav_mid360 as nav
from builtin_interfaces.msg import Time
from rclpy.action import ActionServer


def completed(value):
    future = Future()
    future.set_result(value)
    return future


class SimClock:
    def __init__(self):
        self.now = 100.0
        self.step = lambda dt: None

    def monotonic(self):
        return self.now

    def sleep(self, dt):
        self.step(dt)
        self.now += dt


class SimPose:
    def __init__(self, clock, x=0.0, y=0.0, yaw=0.0):
        self.clock = clock
        self.x, self.y, self.yaw = x, y, math.radians(yaw)
        self.freeze_at = math.inf

    def get_pose(self):
        return self.x, self.y, self.yaw, min(self.clock.monotonic(), self.freeze_at)

    def get_clock(self):
        return SimpleNamespace(now=lambda: SimpleNamespace(to_msg=lambda: Time(sec=1)))


class SimSender:
    def __init__(self, pose, turn_sign=1):
        self.pose = pose
        self.turn_sign = turn_sign
        self.commands = []
        self.current = (nav.motion_channels(), 0, 0)
        self.stops = 0
        self.pose.clock.step = self.advance

    def send(self, channels, yaw=0, des_yaw=0):
        nav.build_frame(0, channels, yaw, des_yaw)  # 同时校验打包范围
        self.current = (channels, yaw, des_yaw)
        self.commands.append(self.current)

    def stop(self):
        self.stops += 1
        self.send(nav.motion_channels(), 0, 0)

    def advance(self, dt):
        channels, yaw, desired = self.current
        p = self.pose
        forward, left = channels[2] * 4.0 / 600.0, channels[0] * 4.0 / 600.0
        p.x += (math.cos(p.yaw) * forward - math.sin(p.yaw) * left) * dt
        p.y += (math.sin(p.yaw) * forward + math.cos(p.yaw) * left) * dt
        if desired != 0:
            p.yaw += self.turn_sign * 0.00059 * (desired - yaw) * dt
            p.yaw = math.radians(nav.norm_deg(math.degrees(p.yaw)))


def planner_reply(points, status=nav.GoalStatus.STATUS_SUCCEEDED, frame="map", error=0):
    result = nav.ComputePathToPose.Result()
    result.path.header.frame_id = frame
    if hasattr(result, "error_code"):
        result.error_code = error
    for x, y in points:
        point = nav.PoseStamped()
        point.header.frame_id = frame
        point.pose.position.x, point.pose.position.y = float(x), float(y)
        result.path.poses.append(point)
    return SimpleNamespace(status=status, result=result)


class NavigationTests(unittest.TestCase):
    def setUp(self):
        self.clock = SimClock()
        self.pose = SimPose(self.clock)
        self.sender = SimSender(self.pose)
        self.clock_patch = patch.object(nav, "time", self.clock)
        self.clock_patch.start()
        self.addCleanup(self.clock_patch.stop)
        self.output = io.StringIO()
        self.output_patch = contextlib.redirect_stdout(self.output)
        self.output_patch.__enter__()
        self.addCleanup(self.output_patch.__exit__, None, None, None)

    def client_for(self, reply):
        handle = Mock(accepted=True)
        handle.get_result_async.return_value = completed(reply)
        client = Mock()
        client.send_goal_async.return_value = completed(handle)
        return client, handle

    def test_frame_layout_and_crc_unchanged(self):
        frame = nav.build_frame(65535, nav.motion_channels(12, 34), 17900, 18100)
        self.assertEqual(len(frame), 34)
        self.assertEqual(frame[:4], b'\xa5\x5a\x1c\x01')
        self.assertEqual(struct.unpack('<H10h3h', frame[4:-2])[-3:], (17900, 18100, 0))
        self.assertEqual(struct.unpack('<H', frame[-2:])[0], nav.crc16_ccitt(frame[2:-2]))

    def test_heading_wrap_and_zero_target(self):
        for current, target, sign in ((179, -177, 1), (-179, 177, -1), (45, 0, -1)):
            yaw, desired = nav.heading_command(current, target)
            self.assertGreater((desired - yaw) * sign, 0)
            self.assertLessEqual(abs(desired - yaw), nav.MAX_YAW_COMMAND_DEG * 100 + 1)
        self.assertNotEqual(nav.heading_command(0, 0)[1], 0)
        self.assertNotEqual(nav.heading_command(4, 0)[1], 0)

    def test_heading_encoding_over_full_circle(self):
        for current in range(-180, 181, 5):
            for target in range(-360, 361, 15):
                yaw, desired = nav.heading_command(current, target)
                self.assertLessEqual(abs(desired - yaw), 801)
                self.assertNotEqual(desired, 0)
                nav.build_frame(0, nav.motion_channels(), yaw, desired)

    def test_turn_reaches_across_angle_boundary(self):
        self.pose.yaw = math.radians(175)
        self.assertTrue(nav.pid_turn_to(self.sender, self.pose, -170))
        self.assertLessEqual(abs(nav.norm_deg(-170 - math.degrees(self.pose.yaw))), nav.TURN_TOL_DEG)

    def test_large_turn_is_bounded_and_converges(self):
        self.assertTrue(nav.pid_turn_to(self.sender, self.pose, 170))
        self.assertLessEqual(max(abs(d-y) for _, y, d in self.sender.commands), 801)

    def test_reversed_turn_setting(self):
        self.sender.turn_sign = -1
        with patch.object(nav, "TURN_COMMAND_SIGN", -1):
            self.assertTrue(nav.pid_turn_to(self.sender, self.pose, 90))

    def test_frozen_pose_stops_turn(self):
        self.pose.freeze_at = self.clock.now
        with self.assertRaisesRegex(nav.NavigationError, "定位未更新"):
            nav.pid_turn_to(self.sender, self.pose, 90)
        self.assertGreater(self.sender.stops, 0)
        self.assertLessEqual(self.clock.now - self.pose.freeze_at, nav.POSE_TIMEOUT + 0.02)

    def test_frozen_pose_stops_drive(self):
        self.pose.freeze_at = self.clock.now - 1
        with self.assertRaisesRegex(nav.NavigationError, "定位未更新"):
            nav.pid_drive_to(self.sender, self.pose, 1, 0, 0)
        self.assertEqual(self.sender.stops, 1)
        self.assertFalse(any(ch[0] or ch[2] for ch, _, _ in self.sender.commands))

    def test_nan_pose_rejected(self):
        self.pose.x = math.nan
        with self.assertRaises(nav.NavigationError):
            nav.fresh_pose(self.pose)

    def test_turn_timeout_is_failure(self):
        self.clock.step = lambda _: None
        self.assertFalse(nav.pid_turn_to(self.sender, self.pose, 90, timeout=0.1))
        self.assertGreater(self.sender.stops, 0)

    def test_curved_path_and_final_heading(self):
        points = [(0.0, 0.0), (0.2, 0.0), (0.4, 0.1), (0.4, 0.3), (0.5, 0.5)]
        nav.follow_path(self.sender, self.pose, points, 0.5, 0.5, 90)
        self.assertLessEqual(math.hypot(self.pose.x - 0.5, self.pose.y - 0.5), nav.STOP_DISTANCE)
        self.assertLessEqual(abs(nav.norm_deg(90-math.degrees(self.pose.yaw))), nav.TURN_TOL_DEG)
        self.assertIn("到达复核", self.output.getvalue())

    def test_failed_waypoint_never_reports_arrival(self):
        with patch.object(nav, "pid_drive_to", return_value=False), patch.object(nav, "pid_turn_to") as turn:
            with self.assertRaisesRegex(nav.NavigationError, "路径执行失败"):
                nav.follow_path(self.sender, self.pose, [(1, 0)], 1, 0, 0)
        turn.assert_not_called()
        self.assertNotIn("到达复核", self.output.getvalue())

    def test_failed_final_heading_never_reports_arrival(self):
        with patch.object(nav, "pid_turn_to", return_value=False):
            with self.assertRaisesRegex(nav.NavigationError, "朝向调整失败"):
                nav.follow_path(self.sender, self.pose, [(0, 0)], 0, 0, 90)
        self.assertNotIn("到达复核", self.output.getvalue())

    def test_short_path_cannot_claim_distant_goal(self):
        with self.assertRaisesRegex(nav.NavigationError, "实际位置"):
            nav.follow_path(self.sender, self.pose, [(0, 0)], 1, 0, 0)

    def test_rotation_drift_fails_final_position_check(self):
        def drift(*args):
            self.pose.x = 0.3
            return True
        with patch.object(nav, "pid_turn_to", side_effect=drift):
            with self.assertRaisesRegex(nav.NavigationError, "最终复核"):
                nav.follow_path(self.sender, self.pose, [(0, 0)], 0, 0, 0)

    def test_planning_uses_robot_start_and_never_spins(self):
        client, _ = self.client_for(planner_reply([(0, 0), (1, 0)]))
        with patch.object(nav.rclpy, "spin_until_future_complete", side_effect=AssertionError("second executor")):
            self.assertEqual(nav.plan_path(client, self.pose, 1, 0), [(0, 0), (1, 0)])
        goal = client.send_goal_async.call_args.args[0]
        self.assertTrue(goal.use_start)
        self.assertEqual(goal.planner_id, "GridBased")

    def test_aborted_action_rejected_even_with_path(self):
        client, _ = self.client_for(planner_reply([(1, 0)], status=nav.GoalStatus.STATUS_ABORTED))
        with self.assertRaisesRegex(nav.NavigationError, "规划失败"):
            nav.plan_path(client, self.pose, 1, 0)

    def test_bad_paths_rejected(self):
        for points, frame in (([], "map"), ([(1, 0)], "odom"), ([(math.nan, 0)], "map"), ([(0.7, 0)], "map")):
            with self.subTest(points=points, frame=frame):
                client, _ = self.client_for(planner_reply(points, frame=frame))
                with self.assertRaises(nav.NavigationError):
                    nav.plan_path(client, self.pose, 1, 0)

    def test_planning_timeout_cancels_action(self):
        client, handle = self.client_for(planner_reply([(1, 0)]))
        with patch.object(nav, "wait_future", side_effect=[True, False]):
            with self.assertRaisesRegex(nav.NavigationError, "规划超时"):
                nav.plan_path(client, self.pose, 1, 0)
        handle.cancel_goal_async.assert_called_once()

    def test_late_goal_acceptance_is_cancelled(self):
        pending = Future()
        client = Mock()
        client.send_goal_async.return_value = pending
        with patch.object(nav, "wait_future", return_value=False):
            with self.assertRaisesRegex(nav.NavigationError, "接收规划请求超时"):
                nav.plan_path(client, self.pose, 1, 0)
        handle = Mock(accepted=True)
        pending.set_result(handle)
        handle.cancel_goal_async.assert_called_once()

    def run_main(self, *, check_only=False, drive_failure=False, nav_ready=True):
        localizer = Mock()
        localizer.get_pose.side_effect = self.pose.get_pose
        sender = Mock()
        client = Mock()
        client.wait_for_server.return_value = nav_ready
        arguments = ["nav_mid360.py"] + (["--check-only"] if check_only else [])
        with contextlib.ExitStack() as stack:
            stack.enter_context(patch.object(nav, "remove_ros_args", return_value=arguments))
            stack.enter_context(patch.object(nav.rclpy, "init"))
            stack.enter_context(patch.object(nav.rclpy, "try_shutdown"))
            stack.enter_context(patch.object(nav, "Localizer", return_value=localizer))
            stack.enter_context(patch.object(nav, "SingleThreadedExecutor"))
            stack.enter_context(patch.object(nav, "ActionClient", return_value=client))
            sender_factory = stack.enter_context(patch.object(nav, "Sender", return_value=sender))
            stack.enter_context(patch.object(nav, "load_points", return_value=(None, [(1.0, 0.0, 0.0)])))
            stack.enter_context(patch("builtins.input", return_value="y"))
            stack.enter_context(patch.object(nav, "plan_path", return_value=[(0, 0), (1, 0)]))
            drive = stack.enter_context(patch.object(nav, "pid_drive_to", return_value=not drive_failure))
            status = nav.main()
        return status, sender_factory, sender, drive

    def test_main_failure_returns_nonzero_and_closes_sender(self):
        status, _, sender, _ = self.run_main(drive_failure=True)
        self.assertEqual(status, 1)
        sender.close.assert_called_once()
        self.assertNotIn("到达 ✅", self.output.getvalue())
        self.assertNotIn("\n导航结束", self.output.getvalue())

    def test_check_only_never_connects_or_drives(self):
        status, sender_factory, _, drive = self.run_main(check_only=True)
        self.assertEqual(status, 0)
        sender_factory.assert_not_called()
        drive.assert_not_called()

    def test_unavailable_nav2_never_falls_back_to_direct_drive(self):
        status, sender_factory, _, drive = self.run_main(nav_ready=False)
        self.assertEqual(status, 1)
        sender_factory.assert_not_called()
        drive.assert_not_called()


class RosExecutorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.logs = tempfile.TemporaryDirectory(prefix=".nav_test_logs_", dir=Path(__file__).parent)
        cls.environment = patch.dict(os.environ, {"ROS_LOG_DIR": cls.logs.name,
                                                  "ROS_DOMAIN_ID": "173",
                                                  "ROS_LOCALHOST_ONLY": "1"})
        cls.environment.start()
        nav.rclpy.init()

    @classmethod
    def tearDownClass(cls):
        nav.rclpy.shutdown()
        cls.environment.stop()
        cls.logs.cleanup()

    def test_action_preserves_executor_and_odometry_callbacks(self):
        localizer = nav.Localizer()
        server_node = nav.Node("test_mid360_planner")
        executor = nav.SingleThreadedExecutor()
        executor.add_node(localizer)
        executor.add_node(server_node)

        def odom_tick():
            msg = nav.Odometry()
            msg.header.frame_id = "world"
            msg.header.stamp = localizer.get_clock().now().to_msg()
            msg.pose.pose.orientation.w = 1.0
            localizer._cb(msg)

        timer = localizer.create_timer(0.01, odom_tick)
        action_name = "/test_compute_path_" + uuid.uuid4().hex

        def execute(handle):
            goal = handle.request.goal.pose.position
            result = planner_reply([(0, 0), (goal.x, goal.y)]).result
            handle.succeed()
            return result

        server = ActionServer(server_node, nav.ComputePathToPose, action_name, execute)
        client = nav.ActionClient(localizer, nav.ComputePathToPose, action_name)
        thread = threading.Thread(target=executor.spin, daemon=True)
        thread.start()
        try:
            self.assertTrue(client.wait_for_server(timeout_sec=5.0))
            deadline = time.monotonic() + 2.0
            while localizer.get_pose()[3] == 0 and time.monotonic() < deadline:
                time.sleep(0.01)
            for goal_x in (1.0, 2.0):
                points = nav.plan_path(client, localizer, goal_x, 0.0)
                self.assertEqual(points[-1], (goal_x, 0.0))
                self.assertIn(localizer, executor.get_nodes())
                self.assertIs(localizer.executor, executor)
                before = localizer.get_pose()[3]
                time.sleep(0.06)
                self.assertGreater(localizer.get_pose()[3], before)
            # 回调仍在接收旧消息时，也不能把重复时间戳当成新定位。
            localizer.destroy_timer(timer)
            time.sleep(0.03)
            before = localizer.get_pose()[3]
            old = nav.Odometry()
            old.header.frame_id = "world"
            old.header.stamp = Time(sec=1)
            old.pose.pose.orientation.w = 1.0
            localizer._cb(old)
            self.assertEqual(localizer.get_pose()[3], before)
        finally:
            executor.shutdown()
            thread.join(timeout=2.0)
            client.destroy()
            server.destroy()
            localizer.destroy_node()
            server_node.destroy_node()


if __name__ == "__main__":
    unittest.main(verbosity=2)
