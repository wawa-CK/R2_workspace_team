# GitHub 完整使用教程 - rc_workspace_team

## 📋 基本信息

- **GitHub 账号**: hanxie208-jpg (豌豆炮，不爽就开炮)
- **工作空间**: rc_workspace_team
- **本地路径**: /home/xiehan/rc_workspace_team (假设)

---

## 🚀 第一次上传完整空间

### Step 1: 在 GitHub 上创建仓库

1. 打开浏览器，访问 https://github.com
2. 登录账号: **hanxie208-jpg**
3. 点击右上角 `+` → `New repository`
4. 填写信息:
   - Repository name: `rc_workspace_team`
   - Description: `R2机器人控制工作空间`
   - 选择 `Public` 或 `Private` (建议 Private)
   - ❌ 不要勾选 "Initialize this repository with a README"
5. 点击 `Create repository`

### Step 2: 初始化本地仓库并上传

```bash
cd /home/xiehan/rc_workspace_team

# 1. 初始化 git 仓库
git init

# 2. 配置用户信息 (如果还没配置)
git config --global user.name "hanxie208-jpg"
git config --global user.email "your_email@example.com"  # 改成你的邮箱

# 3. 创建 .gitignore (排除不需要上传的文件)
cat > .gitignore << 'EOF'
# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
build/
dist/
*.egg-info/

# ROS
install/
log/
build/

# 编辑器
.vscode/
.idea/
*.swp
*~

# 系统文件
.DS_Store
Thumbs.db

# 临时文件
*.log
*.tmp
*.bak
EOF

# 4. 添加所有文件
git add .

# 5. 第一次提交
git commit -m "初始提交: 完整的 rc_workspace_team 工作空间"

# 6. 连接到 GitHub 远程仓库
git remote add origin https://github.com/hanxie208-jpg/rc_workspace_team.git

# 7. 推送到 GitHub
git branch -M main
git push -u origin main
```

**输入账号密码时的注意事项:**
- GitHub 已不支持密码登录，需要使用 **Personal Access Token**
- 如何获取 Token 见下面的说明

---

## 🔑 配置 GitHub Personal Access Token

### 方法 1: 使用 Token (推荐)

**获取 Token:**

1. 登录 GitHub
2. 点击右上角头像 → `Settings`
3. 左侧菜单最下方 → `Developer settings`
4. 左侧 → `Personal access tokens` → `Tokens (classic)`
5. 点击 `Generate new token` → `Generate new token (classic)`
6. 填写:
   - Note: `rc_workspace_team_token`
   - Expiration: `No expiration` (或选择有效期)
   - 勾选权限: `repo` (全部勾选)
7. 点击 `Generate token`
8. **⚠️ 立即复制 Token！只会显示一次！**

**使用 Token:**

```bash
# 推送时输入:
Username: hanxie208-jpg
Password: 粘贴你的 Token (不是密码)
```

**保存 Token 避免每次输入:**

```bash
# 方式 1: Git 凭据缓存 (推荐)
git config --global credential.helper store
# 下次输入一次后就会保存

# 方式 2: 直接在 URL 中包含 Token
git remote set-url origin https://TOKEN@github.com/hanxie208-jpg/rc_workspace_team.git
# 把 TOKEN 替换成你的实际 Token
```

### 方法 2: 使用 SSH (更安全)

```bash
# 1. 生成 SSH 密钥
ssh-keygen -t ed25519 -C "your_email@example.com"
# 一路回车，使用默认设置

# 2. 复制公钥
cat ~/.ssh/id_ed25519.pub
# 复制输出的内容

# 3. 添加到 GitHub
# GitHub → Settings → SSH and GPG keys → New SSH key
# 粘贴公钥，点击 Add

# 4. 改用 SSH URL
git remote set-url origin git@github.com:hanxie208-jpg/rc_workspace_team.git

# 5. 测试连接
ssh -T git@github.com
```

---

## 📝 日常使用：修改后上传

### 单个文件修改

```bash
# 1. 修改文件后，查看状态
git status

# 2. 添加修改的文件
git add 文件名.py

# 3. 提交，带时间戳
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 修改了文件名.py: 描述修改内容"

# 4. 推送到 GitHub
git push
```

### 多个文件修改

```bash
# 1. 查看所有修改
git status

# 2. 添加所有修改
git add .

# 3. 提交，带时间戳
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 批量更新: 描述本次修改"

# 4. 推送
git push
```

---

## ⏰ 带时间戳的提交

### 标准格式

```bash
# 格式: YYYY-MM-DD HH:MM:SS - 描述
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 添加了 D435i 相机支持"

# 例如:
# 2024-09-21 14:30:25 - 添加了 D435i 相机支持
```

### 带详细信息

```bash
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 标题" -m "详细描述

- 修改了 xxx
- 新增了 yyy
- 修复了 zzz 的 bug"
```

---

## 🔄 版本回滚

### 查看历史提交

```bash
# 查看提交历史
git log

# 查看简洁历史
git log --oneline

# 查看带时间的历史
git log --pretty=format:"%h - %an, %ar : %s"

# 查看图形化历史
git log --oneline --graph --all
```

### 回滚方法

#### 方法 1: 撤销最近的提交 (保留修改)

```bash
# 撤销最近1次提交，但保留修改
git reset --soft HEAD^

# 撤销最近2次提交
git reset --soft HEAD~2

# 修改后重新提交
git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 重新提交"
git push -f  # 强制推送
```

#### 方法 2: 撤销最近的提交 (丢弃修改)

```bash
# ⚠️ 危险操作！会丢失修改！
git reset --hard HEAD^

# 强制推送到 GitHub
git push -f
```

#### 方法 3: 回滚到指定版本

```bash
# 1. 查看历史，找到目标版本的 commit ID
git log --oneline

# 输出示例:
# a1b2c3d (HEAD -> main) 2024-09-21 14:30:25 - 最新提交
# e4f5g6h 2024-09-20 10:15:30 - 上一次提交
# h7i8j9k 2024-09-19 16:45:00 - 之前的提交

# 2. 回滚到指定版本 (保留修改)
git reset --soft h7i8j9k

# 或回滚并丢弃修改
git reset --hard h7i8j9k

# 3. 强制推送
git push -f
```

#### 方法 4: 创建反向提交 (推荐，更安全)

```bash
# 不删除历史，创建一个新的反向提交
git revert HEAD

# 或回滚指定提交
git revert a1b2c3d

# 推送
git push
```

---

## 🔍 查看文件修改历史

```bash
# 查看某个文件的修改历史
git log -- 文件名.py

# 查看某个文件的详细修改
git log -p 文件名.py

# 查看谁修改了哪一行
git blame 文件名.py
```

---

## 🌿 分支管理

### 创建和使用分支

```bash
# 创建新分支
git branch 开发分支

# 切换到新分支
git checkout 开发分支

# 或者一步完成
git checkout -b 开发分支

# 在新分支上工作
git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 开发新功能"
git push -u origin 开发分支

# 切换回主分支
git checkout main

# 合并分支
git merge 开发分支

# 删除分支
git branch -d 开发分支
git push origin --delete 开发分支
```

---

## 📦 常用命令速查

### 基本操作

```bash
# 克隆仓库
git clone https://github.com/hanxie208-jpg/rc_workspace_team.git

# 查看状态
git status

# 查看修改内容
git diff

# 添加文件
git add 文件名        # 添加单个文件
git add .            # 添加所有文件

# 提交
git commit -m "描述"

# 推送
git push

# 拉取最新代码
git pull
```

### 撤销操作

```bash
# 撤销工作区的修改 (未 add)
git checkout -- 文件名

# 撤销暂存区的修改 (已 add，未 commit)
git reset HEAD 文件名

# 修改最近一次提交信息
git commit --amend -m "新的提交信息"
```

### 查看信息

```bash
# 查看远程仓库
git remote -v

# 查看分支
git branch -a

# 查看提交历史
git log --oneline --graph --all
```

---

## 🛠️ 自动化脚本

我已经创建了 `git_helper.sh` 脚本，包含所有常用操作，见同目录下的脚本文件。

使用方法:

```bash
./git_helper.sh
```

然后按提示选择操作即可。

---

## ⚠️ 注意事项

### 不要上传的文件

```gitignore
# 大文件
*.bag
*.rosbag
*.mp4
*.avi

# 编译产物
build/
install/
log/

# 敏感信息
*.key
*.pem
config_secret.yaml
```

### 推送前检查

```bash
# 1. 查看即将提交的内容
git status
git diff

# 2. 确认无误后再推送
git push
```

### 冲突解决

```bash
# 如果推送失败，提示冲突
git pull

# 手动解决冲突后
git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 解决冲突"
git push
```

---

## 🎯 实际使用示例

### 示例 1: 修改单个文件

```bash
cd /home/xiehan/rc_workspace_team

# 修改了 test_chassis_basic.py
nano test_chassis_basic.py

# 查看修改
git diff test_chassis_basic.py

# 提交
git add test_chassis_basic.py
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 优化了底盘测试脚本的错误处理"
git push
```

### 示例 2: 添加新功能

```bash
# 创建新分支
git checkout -b feature-新相机支持

# 开发...
git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S') - 添加了新相机驱动"
git push -u origin feature-新相机支持

# 测试通过后，合并到主分支
git checkout main
git merge feature-新相机支持
git push

# 删除功能分支
git branch -d feature-新相机支持
git push origin --delete feature-新相机支支
```

### 示例 3: 紧急回滚

```bash
# 发现最新提交有问题，立即回滚
git log --oneline  # 找到上一个好的版本

# 回滚到上一个版本
git reset --hard HEAD^
git push -f

# 或者创建反向提交（更安全）
git revert HEAD
git push
```

---

## 📚 学习资源

- [Git 官方文档](https://git-scm.com/doc)
- [GitHub 使用教程](https://docs.github.com/cn)
- [Git 可视化学习](https://learngitbranching.js.org/?locale=zh_CN)

---

## 🆘 常见问题

### 1. 推送失败: "rejected"

```bash
# 原因: 远程仓库有新的提交
# 解决:
git pull --rebase
git push
```

### 2. 忘记提交信息怎么办?

```bash
# 修改最近一次提交信息
git commit --amend -m "新的提交信息"
git push -f
```

### 3. 不小心提交了敏感文件

```bash
# 从历史中彻底删除
git filter-branch --force --index-filter \
  "git rm --cached --ignore-unmatch 敏感文件" \
  --prune-empty --tag-name-filter cat -- --all

git push -f
```

### 4. 如何忽略已跟踪的文件?

```bash
# 停止跟踪但保留文件
git rm --cached 文件名

# 添加到 .gitignore
echo "文件名" >> .gitignore

git commit -m "停止跟踪文件"
git push
```

---

**创建日期:** 2024年9月  
**作者:** hanxie208-jpg (豌豆炮，不爽就开炮)  
**仓库:** rc_workspace_team
