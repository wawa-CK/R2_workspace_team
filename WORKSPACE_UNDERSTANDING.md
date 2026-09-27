# R2_H 工作空间理解记录

> 阅读范围：`/home/slam/r2_ws` 当前工作区及其主要源码、启动文件、配置和已有 README。
>
> 记录日期：2026-09-27
>
> 这份文档描述代码当前呈现出来的架构和运行方式。它不是机械结构、下位机固件或现场安全规范的替代品；涉及运动、吸盘、武器和上下楼动作时，必须以实机测试结果为准。

## 1. 项目定位

这个仓库是 R2_H 机器人上位机工程，主要由两条相关但相对独立的应用链组成：

1. **Mid360 + Super-LIO 建图/重定位 + Nav2 规划链**：位于 `test_demo/`，用于采集三维点云、生成二维地图、记录目标点，并沿 Nav2 规划路径用 PID 控制底盘。
2. **正式比赛控制链**：入口是 `competition_script.py`，通过 ROS2 定位、相机二维码、梅林路径规划和 TCP 控制帧完成武林、梅林、九宫格等比赛区域动作。

仓库还集成了两个传感器/算法工作区：

- `lidar_ws/`：Livox ROS2 驱动和 Super-LIO 源码及其构建结果。
- `odin1_ws/`：Odin 传感器 ROS 驱动，负责主机 SDK、点云/深度/图像投影和重定位相关能力。

因此，仓库并不是一个单一 ROS 包。它同时包含 ROS2 C++ 节点、Python ROS2 脚本、比赛动作库、设备 SDK、地图资产、测试脚本和多个历史版本。

## 2. 顶层目录

| 路径 | 职责 | 说明 |
| --- | --- | --- |
| `competition_script.py` | 正式比赛主入口 | 选择场地、赛制、策略，初始化硬件并串联比赛区域 |
| `ultimate_test_script.py` | 分项动作调试入口 | 底盘、旋转、吸盘、KFS、武器、上下楼、九宫格等单项测试 |
| `race.py` | 早期/独立规划工具 | 梅林网格、红蓝场映射、路径代价和可视化；正式流程主要通过 `utils/` 调用 |
| `d455.py` | RealSense 二维码调试 | 独立相机取流和二维码检测 |
| `measure.py` | Odin 定位打点 | ROS2 `/tf` 或相关定位数据上的场地坐标测量 |
| `measure_lidar.py` | 雷达坐标测量 | 持续打印雷达位姿，适合重新测量 odom 起点 |
| `measure_weapon.py` | weapon 点位测量 | 输出武器目标点和朝向 |
| `lib2/` | 比赛硬件与编排库 | 发帧、定位后端、底盘、KFS、武器、动作矩阵执行 |
| `utils/` | 比赛感知与规划库 | 相机图像源、二维码检测、二维码到路径和动作矩阵 |
| `test_demo/` | Mid360 建图导航演示 | 当前打开的 `map.launch.py` 属于这里 |
| `test_9_26/` | 较新的建图/导航实验版本 | 包含增强版打点程序和 PCD 处理工具 |
| `src/livox_ros_driver2/` | Livox 驱动副本 | 含 `COLCON_IGNORE`，通常不应与 `lidar_ws/src` 同时作为构建源 |
| `lidar_ws/src/livox_ros_driver2/` | 活跃 Livox ROS 驱动源码 | ROS1/ROS2 双版本、MID360 配置和启动文件 |
| `lidar_ws/src/Super-LIO/` | Super-LIO 源码 | ROS2 激光惯性里程计、建图、重定位和 RViz 配置 |
| `odin1_ws/src/odin_ros_driver/` | Odin ROS 驱动源码 | C++ 节点、服务、校准、深度和点云重投影 |
| `image/` | 图像/标定资料 | 例如相机外参文件 |
| `git教程/` | Git 使用笔记 | 与机器人运行时无关 |
| `build/`, `install/`, `log/` 及各工作区同名目录 | 构建/运行产物 | 不属于核心源码，不能据此判断源码是否已重新构建 |

### 重复源码和工作区关系

当前至少存在两份 `livox_ros_driver2`：

- `lidar_ws/src/livox_ros_driver2/` 是 `lidar_ws` 内的 ROS2 源码；
- 根目录 `src/livox_ros_driver2/` 看起来是同步副本，并带有 `COLCON_IGNORE`。

实际启动时通过 `FindPackageShare("livox_ros_driver2")` 找到的是当前被 source 的 ROS 工作区安装包。修改源码后应确认改的是被构建并 source 的那一份，并重新执行对应工作区的 `colcon build`。

## 3. 总体数据流

```text
Livox MID360
    │ UDP（配置文件中的 192.168.1.x）
    ▼
livox_ros_driver2
    ├── /livox/lidar
    └── /livox/imu
            │
            ▼
Super-LIO
    ├── /lio/imu/odom
    ├── /lio/robo/odom
    ├── /lio/cloud_world
    ├── TF world -> imu
    └── map.pcd（建图模式保存）
            │
            ├── test_demo/maping_mid360.py
            │       ├── map3d.pcd
            │       ├── map2d.pgm + map2d.yaml
            │       └── points.txt
            │
            └── test_demo/nav.launch.py
                    ├── relocation_node 读取 map.pcd
                    ├── Nav2 map_server / planner_server
                    └── nav_mid360.py 读取 /lio/robo/odom 并控制底盘

Odin ROS driver ──> /tf、/odin1/flag1、图像/点云/深度
RealSense D435i/D455 ──> utils.process / d455.py ──> 二维码
二维码 ──> utils.challenge_lib ──> ACTION_MATRIX_QUEUE
比赛脚本 ──> lib2.module / lib2.compete_logic ──> TCP 192.168.2.199:5000
```

需要区分两个坐标命名习惯：Super-LIO 的点云和里程计通常使用 `world` 作为 frame，Nav2 在 `test_demo` 中通过静态 TF 把 `map` 与 `world` 视为同一坐标系；比赛库则进一步处理 Odin/Mid360 后端、红蓝场镜像和雷达到车体的外参。

## 4. ROS 工作区和依赖

### 4.1 `lidar_ws`

`lidar_ws/src` 包含：

- `livox_ros_driver2`：Livox ROS1/ROS2 驱动和自定义点消息；
- `Super-LIO`：由 `basic` 和 `super_lio` 等包构成的 ROS2 激光惯性里程计系统。

常用构建和使用方式应以当前系统实际 ROS 发行版为准。仓库文档多数按 Humble 写，但 `test_demo/maping_mid360.py` 的注释也出现过 Jazzy，不能把发行版写死为代码事实。

```bash
source /opt/ros/humble/setup.bash
cd /home/slam/r2_ws/lidar_ws
colcon build --symlink-install
source install/setup.bash
```

如果系统实际是 Jazzy，应把 `/opt/ros/humble` 替换成对应发行版，同时重新核对 Nav2、消息包和 ABI。

### 4.2 `odin1_ws`

`odin1_ws/src/odin_ros_driver` 是一个 ament CMake ROS2 包。其 ROS2 启动文件会启动：

- `host_sdk_sample`：设备 SDK 主节点；
- `pcd2depth_ros2_node`：点云转深度；
- `cloud_reprojection_ros2_node`：点云重投影；
- `image_overlay_node`：图像叠加；
- RViz2。

启动文件通过 `ODIN_CALIB_DIR`、`ROS_HOME` 或 `~/.ros/odin_ros_driver` 决定可写的 `calib.yaml` 目录。校准文件路径应与主机 SDK 写入路径一致。

### 4.3 Python 依赖

常见依赖包括：

- ROS2 Python：`rclpy`、`nav_msgs`、`sensor_msgs`、`sensor_msgs_py`、`geometry_msgs`、`nav2_msgs`；
- 图像和二维码：`opencv-python`/`cv2`、`numpy`，RealSense 模式还需要 `pyrealsense2`；
- 地图和工具：`PyYAML`、`Pillow`，部分实验脚本使用 SciPy 或 Matplotlib；
- 系统/设备：ROS2、Nav2、PCL、Livox SDK 依赖、可访问的 UDP/TCP 网络。

仓库没有统一的 `requirements.txt`，所以“Python 能导入”与“设备链路可运行”是两件事，应分别检查。

## 5. Mid360 建图链路

### 5.1 当前打开的 `test_demo/map.launch.py`

该启动文件只组合两个 Include：

1. `livox_ros_driver2/launch_ROS2/msg_MID360_launch.py`：启动 Livox MID360 驱动，发布 `/livox/lidar` 和 `/livox/imu`；
2. `super_lio/launch/Livox_mid360.py`：启动 `super_lio_node`，并通过 `rviz=false` 关闭自带 RViz。

```bash
source /opt/ros/humble/setup.bash
source /home/slam/r2_ws/lidar_ws/install/setup.bash
ros2 launch /home/slam/r2_ws/test_demo/map.launch.py
```

`map.launch.py` 自身不运行 Python 建图脚本、不保存 `test_demo/map3d.pcd`，它只负责让雷达和 LIO 节点起来。之后需要另一个终端运行：

```bash
python3 /home/slam/r2_ws/test_demo/maping_mid360.py
```

### 5.2 Livox 参数

`msg_MID360_launch.py` 使用 `MID360_config.json`。当前配置中能看到：

- 雷达命令地址：`192.168.1.3`；
- 主机接收地址：`192.168.1.5`；
- 点云类型为自定义 Livox 格式；
- 驱动默认发布频率约 10 Hz；
- 配置中包含命令、点云、IMU 和日志端口。

如果实际网卡地址不是 `192.168.1.5`，驱动可能启动但收不到数据；这属于现场网络配置，不是 Python 脚本问题。

### 5.3 Super-LIO 建图模式

`Livox_mid360.py` 加载 `config/livox_360.yaml` 并启动 `super_lio_node`。关键参数包括：

- 激光话题 `/livox/lidar`、IMU 话题 `/livox/imu`；
- Livox 激光类型、盲区、最大量程和体素降采样；
- 激光到 IMU 外参：平移约 `[-0.011, -0.02329, 0.04412]`，旋转矩阵为单位阵；
- 建图保存目录 `map`、地图名 `map.pcd`；
- 发布机器人里程计、地图和稠密点云。

Super-LIO 的 ROS 包源码显示的主要输出为：

| 输出 | 含义 |
| --- | --- |
| `/lio/imu/odom` | IMU 状态里程计 |
| `/lio/robo/odom` | 机器人参考点位姿，建图/导航脚本主要使用它 |
| `/lio/cloud_world` | 已变换到 `world` 坐标的点云，`maping_mid360.py` 订阅它 |
| `/lio/robo/cloud_world` | 机器人相关点云输出 |
| `world -> imu` TF | LIO 当前姿态 |

### 5.4 `maping_mid360.py` 的工作方式

该脚本创建一个 ROS2 节点并在后台线程 spin：

1. 订阅 `/lio/cloud_world` 和 `/lio/robo/odom`；
2. 对每个点按 `VOXEL_SIZE=0.15 m` 建立 `(gx, gy, gz)` 字典，在线去重以控制内存；
3. 每 2 秒把高度 `0.1 m` 到 `2.0 m` 的点投影到 XY，发布 `/mapping_grid`；
4. 首次收到位姿后，把当前位置和 yaw 记录为 `origin`；
5. 输入 `g` 记录目标点，`l` 查看点位，`q` 退出并保存。

保存结果：

- `test_demo/map3d.pcd`：ASCII PCD，在线体素降采样后的三维点；
- `test_demo/map2d.pgm`：由 XY 点投影生成的 PGM；
- `test_demo/map2d.yaml`：Nav2 地图元数据，`origin` 使用点云边界最小 XY；
- `test_demo/map2d.png`：可选的 Pillow 预览图；
- `test_demo/points.txt`：`origin x y yaw` 和多个 `target x y yaw`。

二维栅格生成是简单的障碍投影：满足高度范围的点被标成占用，其他像素先按空闲填充，没有专门的射线清空、膨胀或未知区域推断。因此用于 Nav2 前应检查地图方向、边界、墙体连续性和机器人半径。

## 6. Mid360 重定位和导航链路

### 6.1 `test_demo/nav.launch.py`

该启动文件组合三部分：

1. Livox MID360 驱动；
2. `super_lio/launch/relocation.py`，启动 `relocation_node` 读取 Super-LIO 地图；
3. `test_demo/nav2_bringup.launch.py`，启动地图服务器、全局规划器、两个静态 TF 和 lifecycle manager。

启动前 `nav.launch.py` 会调用 `clean_map_pcd()`：

- 只处理包含 `DATA binary` 的 PCD；
- 假定每个点是 `x y z intensity` 四个 float，共 16 字节；
- 删除坐标绝对值超过 100 m 的点；
- 原文件先保存为 `map.pcd.bak`；
- 更新 PCD header 中的 `WIDTH` 和 `POINTS`。

这能防止已知异常点导致 relocation 的 PCL 索引溢出，但它不验证字段顺序、点大小或 PCD 其他字段，地图格式改变时需要同步修改。

### 6.2 Nav2 配置

`nav2_bringup.launch.py` 当前启动：

- `tf2_ros/static_transform_publisher`：`map -> world` 恒等桥；
- `tf2_ros/static_transform_publisher`：`imu -> base_link` 近似恒等桥；
- `nav2_map_server/map_server`：加载 `test_demo/map2d.yaml`；
- `nav2_planner/planner_server`：提供 `/compute_path_to_pose`；
- lifecycle manager：自动激活 map server 和 planner server。

`nav2_params.yaml` 只配置全局 `NavfnPlanner` 和 global costmap，使用：

- 地图分辨率 `0.05 m`；
- 机器人半径 `0.3 m`；
- 膨胀半径 `0.5 m`；
- `use_astar=true`、允许未知区域。

这里没有完整的 Nav2 controller/local costmap/behavior tree。Nav2 在本项目中的职责主要是计算绕障路径，不直接执行速度控制。

### 6.3 `nav_mid360.py`

该脚本订阅 `/lio/robo/odom`，读取 `points.txt`，连接下位机并完成：

1. 等待定位，最多 30 秒；
2. 读取 `origin` 和目标点；
3. 等待用户输入 `y`；
4. 尝试调用 `/compute_path_to_pose`；
5. Nav2 有路径时，逐个路径点执行“转向 + 位置 PID”；
6. Nav2 不可用或规划失败时，退回目标点直线 PID；
7. 最后转到目标 yaw，结束时发零速帧。

位置控制将世界坐标误差转换到车体坐标：

```text
forward_error = cos(yaw) * dx + sin(yaw) * dy
lateral_error = -sin(yaw) * dx + cos(yaw) * dy
```

默认位置比例增益为 `800`，速度限幅为 `190`，到点阈值为 `0.05 m`，转向容差为 `2°`。这些参数与底盘速度标定和下位机协议相关，不能直接迁移到另一台底盘。

底盘 TCP 参数为 `192.168.2.199:5000`。帧头为 `A5 5A`，类型为 `0x01`，使用 CRC16-CCITT；`ch0` 为横移、`ch2` 为前后、`ch3` 为旋转，yaw 和目标 yaw 以百分之一度编码。正式库 `lib2/tools.py` 也实现了同一协议，但二者是重复实现，后续维护时应避免协议常量漂移。

## 7. 正式比赛控制链

### 7.1 主入口

```bash
python3 /home/slam/r2_ws/competition_script.py
```

`competition_script.py` 的主要职责是交互式配置和流程编排：

- 选择红场/蓝场；
- 选择挑战赛/对抗赛；
- 选择九宫格最终策略；
- 选择 Odin 或 Mid360 定位后端，以及 odom 起点；
- 初始化 `lib2.module`；
- 等待 `/odin1/flag1` 确认重定位或里程计模式；
- 按区域执行或重试武林、梅林和九宫格。

代码中 `rigion` 是历史拼写，语义是 `region`，不要因为拼写误以为是另一套区域。

### 7.2 `lib2` 模块边界

| 文件 | 主要职责 |
| --- | --- |
| `tools.py` | TCP 连接、CRC、V3 帧、持续发帧线程、定位模式监听、坐标/方向辅助、清理 |
| `position_backend.py` | 统一选择 Odin/Mid360 后端和红/蓝场 |
| `position_odin.py` | Odin 场地入口、weapon 目标、台阶和坐标常量 |
| `position_mid360.py` | Mid360 里程计后端及对应坐标 |
| `position_resource.py` | ROS2 订阅 `/lio/robo/odom` 等资源，并按当前后端提供坐标 |
| `move.py` | 原地旋转、位置 PID、底盘驱动、上下楼、锁轮、碰撞/超时处理 |
| `kfs.py` | KFS 吸盘方向、PF2/PF3/双缸选择、吸取/释放和姿态动作 |
| `weapon.py` | weapon 升降、夹爪、模式和触发边沿 |
| `module.py` | 组合动作、初始化、动作矩阵逐行执行、共享状态 |
| `compete_logic.py` | 区域 1/2/3 编排、二维码结果队列、重试和状态恢复 |

发送架构的关键约定是：`frame_thread` 是持续发帧者，业务函数更新共享通道状态；通常不应在业务代码里新建另一个长期 `sendall()` 循环。自动动作通过 `AUTO_TRIGGER_LOCK` 保护模式切换和边沿触发，避免并发覆盖 `ch4~ch7`。

### 7.3 二维码到梅林动作

`utils/process.py` 支持 RealSense 和 Odin 图像源，负责彩色帧预热、二维码候选区域、预处理和 payload 校验。正式比赛脚本会在配置确定后启动后台扫描器，并要求图像源、首帧和识别调用有效；关键感知失败会停止流程。

`utils/challenge_lib.py` 将 12 位 `0/1/2/3` payload 解析为 KFS 布局，再调用 `utils/race.py` 规划路径，最后输出五列动作矩阵：

```text
[from_pos, to_pos, move_dir, height_action, grab_action]
```

- `from_pos` / `to_pos`：台阶编号；
- `move_dir`：统一方向码，代码中映射为 90°、180°、0°、-90°；
- `height_action`：是否执行上下楼；
- `grab_action`：是否吸取 KFS。

`lib2.compete_logic.ACTION_MATRIX_QUEUE` 只传递规划结果，`module.execute_action_matrix()` 负责解释并执行。这样可以独立检查二维码、路径和最终硬件动作。

### 7.4 区域流程

- **区域 1 / 武林**：准备和抓取 weapon，同时等待二维码规划结果或完成入口动作；
- **区域 2 / 梅林**：从动作矩阵队列取出路径，执行移动、转向、上下楼、KFS 吸取和释放；
- **区域 3 / 九宫格**：根据挑战赛或对抗赛策略放置 KFS，并完成最终动作；
- 每个区域有独立重试入口，失败后可重新输入 KFS 数量、二维码或策略。

`ultimate_test_script.py` 是验证这些动作的更合适入口。建议先测试底盘和单个机构，再测试一个组合动作，最后才运行区域全流程。

## 8. 定位、场地和坐标约定

### 定位后端

`position_backend.py` 用整数选择：

- `1`：Odin，通常依赖 `/tf` 和 Odin 标志；
- `2`：Mid360，通常依赖 `/lio/robo/odom`。

切换后端必须通过统一配置函数，让 `move.py`、`position_resource.py` 和其他已缓存的后端同步刷新。只修改一个全局变量可能造成模块之间使用不同坐标源。

### 重定位/里程计模式

正式流程监听 `/odin1/flag1`：代码约定 `True` 表示重定位，`False` 表示 odom。odom 模式会先读取用户选择的雷达起点，再启动位置资源，避免先按原点创建资源后再切换坐标。

### 红蓝场

红蓝场的镜像主要集中在定位和坐标层，动作矩阵方向码不应在执行层重复镜像。新增坐标点时需要同时检查：场地、机器人朝向、雷达到车体外参、weapon 目标和台阶关系。

## 9. 运行命令速查

### 检查 ROS 话题

```bash
source /opt/ros/humble/setup.bash
source /home/slam/r2_ws/lidar_ws/install/setup.bash
ros2 topic list | grep -E 'livox|lio|tf'
ros2 topic echo /lio/robo/odom --once
ros2 topic hz /lio/cloud_world
ros2 run tf2_tools view_frames
```

### 建图

```bash
ros2 launch /home/slam/r2_ws/test_demo/map.launch.py
# 另一个终端
source /opt/ros/humble/setup.bash
source /home/slam/r2_ws/lidar_ws/install/setup.bash
python3 /home/slam/r2_ws/test_demo/maping_mid360.py
```

在建图脚本中按 `g` 记录目标、按 `l` 查看、按 `q` 保存。保存后检查 `map3d.pcd`、`map2d.pgm`、`map2d.yaml` 和 `points.txt`。

### 重定位和导航

```bash
ros2 launch /home/slam/r2_ws/test_demo/nav.launch.py
# 等待驱动、relocation 和 Nav2 就绪后，另一个终端
python3 /home/slam/r2_ws/test_demo/nav_mid360.py
```

启动顺序、雷达上电顺序和网络地址会影响 Livox 握手；若没有 `/lio/robo/odom`，先检查雷达驱动和 Super-LIO，不要先调 PID。

### 手动底盘

```bash
python3 /home/slam/r2_ws/test_demo/hand.py
# w 前进，s 后退，a/d 转向，q 退出
python3 /home/slam/r2_ws/test_demo/demo_move.py
```

这两项只依赖下位机 TCP，不需要定位，但会真实驱动底盘。

### 正式比赛

```bash
python3 /home/slam/r2_ws/competition_script.py
```

建议先运行 `python3 -m py_compile competition_script.py lib2/*.py utils/*.py`，再确认 ROS 话题、二维码图像源和下位机连接。

## 10. 关键文件和持久化资产

| 文件 | 作用 |
| --- | --- |
| `test_demo/map2d.yaml` | 当前 Nav2 地图元数据，引用绝对路径 `/home/slam/r2_ws/test_demo/map2d.pgm` |
| `test_demo/map2d.pgm` / `map2d.png` | 当前二维地图和预览 |
| `test_demo/map3d.pcd` | 建图脚本生成的三维点云 |
| `test_demo/points.txt` | 当前建图起点和目标点；格式为 `origin/target x y yaw` |
| `lidar_ws/src/Super-LIO/src/super_lio/map/map.pcd` | Super-LIO 重定位使用的地图 |
| `.../map.pcd.bak` | `clean_map.py` 或导航启动清理前的备份 |
| `lib2/position_odin.py` | 场地、台阶、入口、weapon 目标等高风险常量 |
| `lib2/tools.py` | 下位机地址、协议字段、速度缩放和定位标志话题 |
| `lidar_ws/src/livox_ros_driver2/config/MID360_config.json` | 雷达和主机网卡/UDP 配置 |
| `odin1_ws/src/odin_ros_driver/config/control_command.yaml` | Odin 运行参数和节点共享配置 |

地图和坐标文件属于运行时状态，不应只看 Git 历史判断是否适合当前场地。重新建图、换场地或调整传感器安装后，必须同步复测目标点和外参。

## 11. 已发现的代码/文档不一致

以下问题不一定表示程序必然不能运行，但运行前值得核对：

1. `README_COMPLETE_WORKFLOW.md` 中使用了 `/home/xiehan/odin1_ws`、`~/ws_livox` 和不存在于当前根目录的脚本名；当前工作区应使用 `/home/slam/r2_ws` 与实际 source 后的安装路径。
2. `test_demo` 文档一部分写 Humble，一部分注释写 Jazzy；ROS 发行版、Nav2 参数和 C++ ABI 应以机器实际安装为准。
3. `maping_mid360.py` 订阅 `/lio/cloud_world`，而 `test_9_26` 的实验脚本默认使用 `/cloud_registered`；这两套脚本不能只替换文件名就互换运行。
4. `map.launch.py` 只启动驱动和 Super-LIO，必须另行运行 `maping_mid360.py` 才会生成 `test_demo` 下的地图。
5. Super-LIO 的 `livox_360.yaml` 建图保存 `map/map.pcd`，而 `test_demo/maping_mid360.py` 另存 `test_demo/map3d.pcd`；导航重定位读取的是 Super-LIO 的 `map.pcd`，不是 Nav2 的 `map2d.pgm`。
6. `nav2_bringup.launch.py` 使用近似恒等的 `map->world` 和 `imu->base_link` TF。若真实安装存在平移、旋转或不同 frame，导航结果会产生系统误差。
7. `nav_mid360.py` 和 `lib2/tools.py` 各自实现 TCP 帧协议；修改协议时要同时检查帧长度、CRC、yaw 编码、停止帧和安全通道。
8. `clean_map.py` 只支持特定 binary PCD 布局；ASCII PCD、不同字段或不同点大小会被跳过或错误解释。
9. `map2d.yaml` 使用绝对路径，换机器、换工作区或把地图拷贝到其他目录后需要更新 `image` 字段。
10. 当前 Git 状态显示 `lidar_ws/src/Super-LIO`、`lidar_ws/src/livox_ros_driver2` 和根目录 `src/livox_ros_driver2` 有修改状态；这些可能是子模块或构建同步结果，提交前应单独确认来源。

## 12. 推荐排查顺序

遇到“导航不动”“定位漂移”或“比赛流程卡住”时，按依赖从底到顶排查：

1. **网络和设备**：确认雷达主机 IP、雷达 IP、下位机 `192.168.2.199:5000` 可达。
2. **驱动**：确认 `/livox/lidar`、`/livox/imu` 有频率正常的数据。
3. **LIO**：确认 `/lio/robo/odom`、`/lio/cloud_world` 和 `world->imu` TF；检查外参和地图路径。
4. **地图**：检查 PCD 是否有异常坐标，PGM/YAML 的 resolution、origin 和坐标方向是否一致。
5. **Nav2**：确认 `map_server`、`planner_server` 已由 lifecycle 激活，`/compute_path_to_pose` 可用，TF 链完整。
6. **控制**：先用空载、低速方式验证 yaw、横移、前后方向和停止帧，再提高 PID 参数。
7. **比赛感知**：确认图像源、二维码 payload、KFS 数量和红蓝场设置，再检查动作矩阵。
8. **机构动作**：最后才测试吸盘、武器、上下楼和区域组合动作，异常时立即走现有清理/急停流程。

## 13. 当前理解的核心设计取舍

- 用单独的后台发帧线程统一输出控制帧，业务模块只更新状态，降低多线程同时写 TCP 的风险。
- 用 `world/map` 坐标中的位置闭环控制底盘，Nav2 只负责路径规划，便于保留现有下位机控制协议。
- 用五列动作矩阵连接二维码/路径规划和机构执行，使规划结果可以打印、校验和重试。
- 通过后端选择、场地镜像和定位资源层集中处理坐标差异，执行层尽量保持统一。
- 对二维码首帧、定位消息、规划服务和地图坏点设置显式等待或失败边界，减少带着无效状态继续运动。

这些设计依赖多个现场假设：雷达网络、安装外参、地图坐标、下位机协议、机械动作时间和场地尺寸。代码层的流程正确并不等于当前实机参数已经正确，迁移或改动后仍需重新测量和低风险验证。
