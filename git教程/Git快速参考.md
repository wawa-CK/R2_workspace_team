# Git 快速参考卡片 - 豌豆炮专用

## 🚀 最常用命令

### 第一次上传

```bash
cd /path/to/rc_workspace_team
./git_helper.sh
# 选择: 1 - 初始化并首次上传
```

### 日常修改后上传

```bash
# 方式 1: 使用脚本 (推荐)
./git_helper.sh
# 选择: 2 - 快速提交并推送

# 方式 2: 手动命令
git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 你的修改描述"
git push
```

### 单个文件上传

```bash
# 方式 1: 使用脚本
./git_helper.sh
# 选择: 3 - 提交指定文件

# 方式 2: 手动命令
git add 文件名.py
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 更新了文件名.py"
git push
```

---

## ⏰ 带时间戳的提交

### 标准格式

```bash
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 描述内容"
```

### 示例

```bash
# 输出类似: 2024-09-21 15:30:45 - 添加了新功能
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 添加了新功能"
```

---

## 🔄 版本回滚

### 回滚到上一版本

```bash
# 使用脚本
./git_helper.sh
# 选择: 9 - 回滚到上一版本

# 手动命令
git reset --soft HEAD^   # 保留修改
git reset --hard HEAD^   # 丢弃修改
git push -f              # 强制推送
```

### 回滚到指定版本

```bash
# 1. 查看历史
git log --oneline

# 2. 回滚
git reset --hard a1b2c3d  # commit ID
git push -f

# 或使用脚本
./git_helper.sh
# 选择: 10 - 回滚到指定版本
```

---

## 🔍 查看信息

```bash
# 查看状态
git status

# 查看修改
git diff

# 查看历史
git log --oneline

# 查看历史(带时间)
git log --pretty=format:"%h - %an, %ar : %s"
```

---

## 📦 克隆和拉取

```bash
# 克隆仓库
git clone https://github.com/hanxie208-jpg/rc_workspace_team.git

# 拉取最新代码
git pull
```

---

## ⚙️ 一次性配置

```bash
# 配置用户信息
git config --global user.name "hanxie208-jpg"
git config --global user.email "your_email@example.com"

# 保存凭据
git config --global credential.helper store

# 或使用脚本
./git_helper.sh
# 选择: 18 - 配置用户信息
# 选择: 19 - 配置 Token/SSH
```

---

## 🆘 紧急情况

### 推送失败

```bash
# 拉取最新代码
git pull --rebase
git push
```

### 撤销未提交的修改

```bash
# 撤销单个文件
git checkout -- 文件名

# 撤销所有修改
git reset --hard HEAD
```

### 修改最近的提交信息

```bash
git commit --amend -m "新的提交信息"
git push -f
```

---

## 📱 使用脚本的优势

```bash
./git_helper.sh
```

**功能:**
- ✅ 自动添加时间戳
- ✅ 交互式选择文件
- ✅ 安全的回滚确认
- ✅ 彩色提示信息
- ✅ 错误检查和提示
- ✅ 一键完成复杂操作

**菜单选项:**
```
1.  初始化并首次上传
2.  快速提交并推送 (最常用)
3.  提交指定文件
8.  查看提交历史
9.  回滚到上一版本
12. 查看当前状态
```

---

## 📝 工作流程

### 场景 1: 修改代码后上传

```bash
cd /path/to/rc_workspace_team

# 1. 查看修改
git status

# 2. 快速上传
./git_helper.sh
# 选择: 2
# 输入描述: 优化了底盘控制逻辑

# 完成！
```

### 场景 2: 修改单个文件

```bash
# 修改文件
nano test.py

# 上传
./git_helper.sh
# 选择: 3
# 输入文件: test.py
# 输入描述: 修复了测试脚本的bug

# 完成！
```

### 场景 3: 发现问题需要回滚

```bash
./git_helper.sh
# 选择: 9 - 回滚到上一版本
# 确认回滚
# 选择是否保留修改
# 完成！
```

---

## 🎯 记忆口诀

```
第一次用: 选 1
平时改完: 选 2
单个文件: 选 3
查看历史: 选 8
版本回滚: 选 9/10
```

---

## 📞 获取帮助

### 脚本内帮助
```bash
./git_helper.sh
# 按提示操作
```

### Git 官方帮助
```bash
git help
git help commit
git help push
```

### 查看完整教程
```bash
cat GitHub使用教程.md
```

---

**账号:** hanxie208-jpg (豌豆炮，不爽就开炮)  
**仓库:** rc_workspace_team  
**脚本:** git_helper.sh
