# Super-LIO + Mid360 建图导航完整方案

## 📋 功能清单

### ✅ 已实现的功能

1. **Super-LIO 3D建图**
   - 实时采集点云 (`/cloud_registered`)
   - 保存为PCD格式
   - 降采样工具

2. **PCD → 2D栅格地图转换**
   - 自动转换为Nav2格式 (.pgm + .yaml)
   - 可调节分辨率和高度过滤

3. **定位功能**
   - Super-LIO里程计 (`/lio/robo/odom`)
   - TF变换 (map→odom)
   - 手动重定位

4. **打点和导航**
   - 记录目标点
   - 依次导航到目标点
   - 精准控制(转向+直行+精调)

5. **完整流程自动化**
   - 一键转换工具链

---

## 🔧 依赖项检查

### Python依赖

```bash
# 检查是否已安装
python3 -c "import numpy; import yaml; from PIL import Image; import rclpy; print('✅ 所有依赖已安装')"

# 如果缺失，安装：
pip3 install numpy pyyaml pillow
pip3 install scipy  # 用于地图膨胀等高级处理
```

### ROS2依赖

```bash
# 检查Super-LIO是否运行
ros2 topic list | grep -E "/lio|/cloud_registered"

# 检查Nav2是否安装
ros2 pkg list | grep nav2

# 如果缺失Nav2:
sudo apt install ros-humble-navigation2 ros-humble-nav2-bringup
```

### 硬件依赖

- ✅ Mid360激光雷达
- ✅ R2_H底盘控制器 (TCP 192.168.2.199:5000)
- ✅ Super-LIO运行

---

## 📁 文件结构

```
/home/xiehan/odin1_ws/
├── demo_mid360_pickpoint.py      # 主程序：建图+打点+导航
├── pcd_downsample.py              # PCD降采样工具
├── superlio_map_pipeline.py       # 完整流程自动化
├── bin_to_nav2_map.py             # (可选) Odin BIN转2D地图
├── maps/                          # 保存的3D地图
│   └── mid360_map_YYYYMMDD_HHMMSS.pcd
├── waypoints/                     # 保存的目标点
│   └── waypoints_YYYYMMDD_HHMMSS.json
└── nav2_maps/                     # 生成的2D栅格地图
    ├── warehouse_map.pgm
    └── warehouse_map.yaml
```

---

## 🚀 完整使用流程

### 步骤1: 启动Super-LIO

```bash
# 在终端1启动Super-LIO
cd ~/ws_livox
source install/setup.bash
ros2 launch super_lio mapping.launch.py
```

### 步骤2: 运行建图和打点程序

```bash
# 在终端2
cd /home/xiehan/odin1_ws
source /opt/ros/humble/setup.bash
source ~/ws_livox/install/setup.bash
python3 demo_mid360_pickpoint.py
```

**操作流程：**
1. **建图**: 输入 `m` 开始建图，推车扫描环境
2. **停止**: 输入 `n` 停止建图
3. **保存**: 输入 `s` 保存PCD文件
4. **打点**: 
   - 输入 `a` 记录当前位置
   - 或输入 `w` 手动输入坐标
5. **保存打点**: 输入 `p` 保存为JSON
6. **导航**: 输入 `g` 依次导航到所有目标点

### 步骤3: 转换为2D地图（用于Nav2）

```bash
# 在终端3
cd /home/xiehan/odin1_ws

# 自动化流程
python3 superlio_map_pipeline.py \
  maps/mid360_map_20240101_120000.pcd \
  --output-name warehouse_map \
  --voxel-size 0.10 \
  --resolution 0.05

# 生成文件:
#  - warehouse_map_downsampled.pcd
#  - warehouse_map.pgm
#  - warehouse_map.yaml
```

### 步骤4: 在Nav2中使用地图

编辑Nav2配置文件或launch文件：

```python
# nav2_params.yaml
map_server:
  ros__parameters:
    yaml_filename: "/home/xiehan/odin1_ws/warehouse_map.yaml"
```

或在launch文件中：

```python
map_server_node = Node(
    package='nav2_map_server',
    executable='map_server',
    parameters=[{
        'yaml_filename': '/home/xiehan/odin1_ws/warehouse_map.yaml'
    }]
)
```

---

## 🔍 功能验证

### 检查Super-LIO话题

```bash
# 检查里程计
ros2 topic echo /lio/robo/odom --once

# 检查点云
ros2 topic hz /cloud_registered

# 检查TF树
ros2 run tf2_tools view_frames
```

### 测试建图流程

```bash
# 1. 运行demo程序
python3 demo_mid360_pickpoint.py

# 2. 输入 'm' 开始建图
# 3. 推车10秒
# 4. 输入 'n' 停止
# 5. 输入 's' 保存
# 6. 检查保存的PCD
ls -lh maps/
```

### 验证2D地图

```bash
# 查看生成的地图文件
eog warehouse_map.pgm

# 检查YAML配置
cat warehouse_map.yaml
```

---

## 📊 参数调优

### 降采样参数

```bash
# 更密集的点云（更大文件）
--voxel-size 0.05

# 更稀疏的点云（更小文件）
--voxel-size 0.20

# 只保留地面到2米的障碍物
--z-min -0.5 --z-max 2.0
```

### 2D地图分辨率

```bash
# 更精细（5cm/像素，文件更大）
--resolution 0.05

# 平衡（10cm/像素，推荐）
--resolution 0.10

# 更粗糙（20cm/像素，文件更小）
--resolution 0.20
```

---

## ⚠️ 常见问题

### 1. 无法连接TCP下位机

**症状**: `❌ TCP 连接失败`

**解决**:
```bash
# 检查网络
ping 192.168.2.199

# 检查端口
nc -zv 192.168.2.199 5000
```

### 2. 没有收到点云

**症状**: `⚠️ 未收到点云 /cloud_registered`

**解决**:
```bash
# 检查Super-LIO是否运行
ros2 topic list | grep cloud_registered

# 重启Super-LIO
```

### 3. 地图文件太大

**症状**: 生成的PGM文件几百MB

**解决**:
```bash
# 方法1: 增大降采样体素
--voxel-size 0.20

# 方法2: 降低2D地图分辨率
--resolution 0.10

# 方法3: 限制地图范围（修改脚本）
```

### 4. 重定位不准确

**症状**: 机器人位置偏移

**解决**:
```bash
# 在demo程序中手动重定位
# 输入 '1'，然后输入当前实际坐标
```

---

## 📝 工作流总结

```
┌─────────────────┐
│  Super-LIO启动  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  建图(推车扫描)  │ ← demo_mid360_pickpoint.py
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  保存3D PCD     │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  降采样+转2D    │ ← superlio_map_pipeline.py
└────────┬────────┘
         │
         ├──→ warehouse_map_downsampled.pcd (3D，用于重定位)
         │
         └──→ warehouse_map.pgm/yaml (2D，Nav2全局地图)
         
         
使用阶段:
─────────
┌─────────────────┐
│  Mid360重定位   │ ← 加载3D PCD，提供初始位姿
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  打点(记录目标)  │ ← demo_mid360_pickpoint.py
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Nav2导航       │ ← 使用2D地图避障
│  (到达目标点)   │
└─────────────────┘
```

---

## ✅ 功能完整性确认

| 功能 | 状态 | 工具/脚本 |
|------|------|----------|
| Super-LIO建图 | ✅ | demo_mid360_pickpoint.py |
| 保存3D PCD | ✅ | demo_mid360_pickpoint.py |
| PCD降采样 | ✅ | pcd_downsample.py |
| PCD→2D地图 | ✅ | superlio_map_pipeline.py |
| Mid360重定位 | ✅ | Super-LIO (手动offset) |
| 打点记录 | ✅ | demo_mid360_pickpoint.py |
| 精准导航 | ✅ | demo_mid360_pickpoint.py |
| Nav2集成 | ✅ | 生成的.yaml文件 |

**结论**: 所有核心功能已完整实现！
