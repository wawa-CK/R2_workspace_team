#!/bin/bash
# Git 助手脚本 
# 账号: 
# 仓库: rc_workspace_team

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 配置
GITHUB_USER="wawa-CK"
REPO_NAME="R2_workspace_team"
DEFAULT_BRANCH="main"

# 打印带颜色的消息
print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

# 获取当前时间戳
get_timestamp() {
    date '+%Y-%m-%d %H:%M:%S'
}

# 检查是否在 git 仓库中
check_git_repo() {
    if ! git rev-parse --git-dir > /dev/null 2>&1; then
        print_error "当前目录不是 Git 仓库"
        print_info "请先运行初始化功能或 cd 到正确的目录"
        return 1
    fi
    return 0
}

# 显示主菜单
show_menu() {
    clear
    echo "=========================================="
    echo "    Git 助手 -"
    echo "=========================================="
    echo ""
    echo "账号: ${GITHUB_USER}"
    echo "仓库: ${REPO_NAME}"
    echo ""
    echo "=========================================="
    echo "  操作菜单"
    echo "=========================================="
    echo ""
    echo "📤 上传操作:"
    echo "  1. 初始化并首次上传完整仓库"
    echo "  2. 快速提交并推送 (所有修改)"
    echo "  3. 提交并推送指定文件"
    echo "  4. 批量提交多个文件"
    echo ""
    echo "📥 下载/更新:"
    echo "  5. 克隆仓库到本地"
    echo "  6. 拉取最新代码"
    echo ""
    echo "⏰ 时间戳相关:"
    echo "  7. 带时间戳提交 (自定义消息)"
    echo "  8. 查看提交历史 (带时间)"
    echo ""
    echo "🔄 版本控制:"
    echo "  9. 回滚到上一个版本"
    echo " 10. 回滚到指定版本"
    echo " 11. 查看版本差异"
    echo ""
    echo "🔍 查看信息:"
    echo " 12. 查看当前状态"
    echo " 13. 查看修改内容"
    echo " 14. 查看文件修改历史"
    echo ""
    echo "🌿 分支管理:"
    echo " 15. 创建新分支"
    echo " 16. 切换分支"
    echo " 17. 合并分支"
    echo ""
    echo "⚙️  配置:"
    echo " 18. 配置用户信息"
    echo " 19. 配置 Token/SSH"
    echo " 20. 查看配置信息"
    echo ""
    echo " 0. 退出"
    echo ""
    echo "=========================================="
}

# 1. 初始化并首次上传
init_and_upload() {
    echo ""
    echo "=========================================="
    echo "  初始化并首次上传仓库"
    echo "=========================================="
    echo ""

    # 检查是否已经初始化
    if [ -d ".git" ]; then
        print_warning "当前目录已经是 Git 仓库"
        read -p "是否继续? (y/n): " confirm
        if [ "$confirm" != "y" ]; then
            return
        fi
    fi

    print_info "步骤 1/6: 初始化 Git 仓库..."
    git init

    print_info "步骤 2/6: 创建 .gitignore..."
    if [ ! -f ".gitignore" ]; then
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
venv/
env/

# ROS
install/
log/
build/

# 编辑器
.vscode/
.idea/
*.swp
*~

# 系统
.DS_Store
Thumbs.db

# 临时文件
*.log
*.tmp
*.bak

# 大文件
*.bag
*.rosbag
*.mp4
*.avi

# 敏感信息
*.key
*.pem
*_secret.*
EOF
        print_success "已创建 .gitignore"
    else
        print_info ".gitignore 已存在"
    fi

    print_info "步骤 3/6: 添加所有文件..."
    git add .

    print_info "步骤 4/6: 创建初始提交..."
    git commit -m "$(get_timestamp) - 初始提交: 完整的 ${REPO_NAME} 工作空间"

    print_info "步骤 5/6: 连接到 GitHub 远程仓库..."
    git remote add origin https://github.com/${GITHUB_USER}/${REPO_NAME}.git 2>/dev/null || \
    git remote set-url origin https://github.com/${GITHUB_USER}/${REPO_NAME}.git

    print_info "步骤 6/6: 推送到 GitHub..."
    git branch -M ${DEFAULT_BRANCH}

    print_warning "首次推送需要输入 GitHub 凭据"
    print_info "用户名: ${GITHUB_USER}"
    print_info "密码: 使用 Personal Access Token (不是密码)"
    echo ""

    if git push -u origin ${DEFAULT_BRANCH}; then
        print_success "初始化并上传成功!"
        echo ""
        print_info "仓库地址: https://github.com/${GITHUB_USER}/${REPO_NAME}"
    else
        print_error "推送失败，请检查网络或凭据"
        echo ""
        print_info "提示: 如需配置凭据，请选择菜单选项 19"
    fi

    read -p "按回车继续..."
}

# 2. 快速提交并推送
quick_commit() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  快速提交并推送"
    echo "=========================================="
    echo ""

    # 显示修改的文件
    echo "修改的文件:"
    git status --short
    echo ""

    read -p "请输入提交描述: " message

    if [ -z "$message" ]; then
        print_warning "未输入描述，使用默认描述"
        message="常规更新"
    fi

    timestamp=$(get_timestamp)
    full_message="${timestamp} - ${message}"

    print_info "添加所有修改..."
    git add .

    print_info "创建提交: ${full_message}"
    git commit -m "${full_message}"

    print_info "推送到 GitHub..."
    if git push; then
        print_success "推送成功!"
    else
        print_error "推送失败"
    fi

    read -p "按回车继续..."
}

# 3. 提交并推送指定文件
commit_specific_file() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  提交指定文件"
    echo "=========================================="
    echo ""

    # 显示修改的文件
    echo "修改的文件:"
    git status --short
    echo ""

    read -p "请输入文件路径: " filepath

    if [ ! -f "$filepath" ]; then
        print_error "文件不存在: $filepath"
        read -p "按回车继续..."
        return
    fi

    read -p "请输入提交描述: " message

    if [ -z "$message" ]; then
        message="更新 ${filepath}"
    fi

    timestamp=$(get_timestamp)
    full_message="${timestamp} - ${message}"

    print_info "添加文件: ${filepath}"
    git add "${filepath}"

    print_info "创建提交: ${full_message}"
    git commit -m "${full_message}"

    print_info "推送到 GitHub..."
    if git push; then
        print_success "推送成功!"
    else
        print_error "推送失败"
    fi

    read -p "按回车继续..."
}

# 4. 批量提交多个文件
commit_multiple_files() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  批量提交多个文件"
    echo "=========================================="
    echo ""

    echo "修改的文件:"
    git status --short
    echo ""

    print_info "输入文件路径，每行一个，输入空行结束:"

    files=()
    while true; do
        read -p "文件 $((${#files[@]}+1)): " filepath
        if [ -z "$filepath" ]; then
            break
        fi
        if [ -f "$filepath" ] || [ -d "$filepath" ]; then
            files+=("$filepath")
        else
            print_warning "文件不存在: $filepath"
        fi
    done

    if [ ${#files[@]} -eq 0 ]; then
        print_warning "未选择任何文件"
        read -p "按回车继续..."
        return
    fi

    echo ""
    echo "将提交以下文件:"
    for f in "${files[@]}"; do
        echo "  - $f"
    done
    echo ""

    read -p "请输入提交描述: " message

    if [ -z "$message" ]; then
        message="批量更新 ${#files[@]} 个文件"
    fi

    timestamp=$(get_timestamp)
    full_message="${timestamp} - ${message}"

    print_info "添加文件..."
    for f in "${files[@]}"; do
        git add "$f"
    done

    print_info "创建提交: ${full_message}"
    git commit -m "${full_message}"

    print_info "推送到 GitHub..."
    if git push; then
        print_success "推送成功!"
    else
        print_error "推送失败"
    fi

    read -p "按回车继续..."
}

# 5. 克隆仓库
clone_repo() {
    echo ""
    echo "=========================================="
    echo "  克隆仓库到本地"
    echo "=========================================="
    echo ""

    read -p "请输入目标目录名 (默认: ${REPO_NAME}): " dir_name

    if [ -z "$dir_name" ]; then
        dir_name="${REPO_NAME}"
    fi

    if [ -d "$dir_name" ]; then
        print_error "目录已存在: $dir_name"
        read -p "按回车继续..."
        return
    fi

    print_info "克隆仓库..."
    git clone https://github.com/${GITHUB_USER}/${REPO_NAME}.git "$dir_name"

    if [ $? -eq 0 ]; then
        print_success "克隆成功!"
        print_info "目录: $(pwd)/$dir_name"
    else
        print_error "克隆失败"
    fi

    read -p "按回车继续..."
}

# 6. 拉取最新代码
pull_latest() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  拉取最新代码"
    echo "=========================================="
    echo ""

    print_info "拉取最新代码..."
    if git pull; then
        print_success "拉取成功!"
    else
        print_error "拉取失败，可能存在冲突"
        print_info "请手动解决冲突后重试"
    fi

    read -p "按回车继续..."
}

# 7. 带时间戳提交
timestamped_commit() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  带时间戳的提交"
    echo "=========================================="
    echo ""

    echo "修改的文件:"
    git status --short
    echo ""

    read -p "请输入详细的提交描述: " message

    if [ -z "$message" ]; then
        print_error "必须输入提交描述"
        read -p "按回车继续..."
        return
    fi

    read -p "是否添加详细说明? (y/n): " add_details

    if [ "$add_details" = "y" ]; then
        echo ""
        echo "输入详细说明 (输入空行结束):"
        details=""
        while true; do
            read line
            if [ -z "$line" ]; then
                break
            fi
            details="${details}\n- ${line}"
        done
    fi

    timestamp=$(get_timestamp)

    git add .

    if [ -n "$details" ]; then
        git commit -m "${timestamp} - ${message}" -m "${details}"
    else
        git commit -m "${timestamp} - ${message}"
    fi

    print_info "推送到 GitHub..."
    if git push; then
        print_success "推送成功!"
    else
        print_error "推送失败"
    fi

    read -p "按回车继续..."
}

# 8. 查看提交历史
view_history() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  提交历史"
    echo "=========================================="
    echo ""

    read -p "显示最近多少条? (默认 10): " count

    if [ -z "$count" ]; then
        count=10
    fi

    echo ""
    git log --oneline --graph --decorate -n "$count"
    echo ""

    read -p "按回车继续..."
}

# 9. 回滚到上一版本
rollback_previous() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  回滚到上一个版本"
    echo "=========================================="
    echo ""

    echo "当前版本:"
    git log --oneline -n 1
    echo ""
    echo "上一个版本:"
    git log --oneline -n 1 HEAD^
    echo ""

    print_warning "⚠️  此操作将撤销最近的提交!"
    read -p "确定要回滚吗? (y/n): " confirm

    if [ "$confirm" != "y" ]; then
        print_info "已取消"
        read -p "按回车继续..."
        return
    fi

    read -p "是否保留本地修改? (y=保留/n=丢弃): " keep_changes

    if [ "$keep_changes" = "y" ]; then
        git reset --soft HEAD^
        print_success "已回滚，修改已保留在暂存区"
    else
        git reset --hard HEAD^
        print_success "已回滚，修改已丢弃"
    fi

    read -p "是否立即推送到 GitHub? (y/n): " push_now

    if [ "$push_now" = "y" ]; then
        print_warning "强制推送中..."
        git push -f
        print_success "已推送"
    fi

    read -p "按回车继续..."
}

# 10. 回滚到指定版本
rollback_specific() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  回滚到指定版本"
    echo "=========================================="
    echo ""

    echo "最近的提交:"
    git log --oneline -n 20
    echo ""

    read -p "请输入目标 commit ID (前7位即可): " commit_id

    if [ -z "$commit_id" ]; then
        print_error "未输入 commit ID"
        read -p "按回车继续..."
        return
    fi

    # 验证 commit ID
    if ! git cat-file -e "$commit_id" 2>/dev/null; then
        print_error "无效的 commit ID"
        read -p "按回车继续..."
        return
    fi

    echo ""
    echo "目标版本:"
    git log --oneline -n 1 "$commit_id"
    echo ""

    print_warning "⚠️  此操作将回滚到指定版本!"
    read -p "确定要回滚吗? (y/n): " confirm

    if [ "$confirm" != "y" ]; then
        print_info "已取消"
        read -p "按回车继续..."
        return
    fi

    read -p "是否保留本地修改? (y=保留/n=丢弃): " keep_changes

    if [ "$keep_changes" = "y" ]; then
        git reset --soft "$commit_id"
        print_success "已回滚到 $commit_id，修改已保留"
    else
        git reset --hard "$commit_id"
        print_success "已回滚到 $commit_id，修改已丢弃"
    fi

    read -p "是否立即强制推送? (y/n): " push_now

    if [ "$push_now" = "y" ]; then
        print_warning "强制推送中..."
        git push -f
        print_success "已推送"
    fi

    read -p "按回车继续..."
}

# 11. 查看版本差异
view_diff() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  查看版本差异"
    echo "=========================================="
    echo ""

    echo "1. 查看工作区修改 (未 add)"
    echo "2. 查看暂存区修改 (已 add，未 commit)"
    echo "3. 查看两个版本间的差异"
    echo ""

    read -p "请选择 (1/2/3): " choice

    case $choice in
        1)
            git diff
            ;;
        2)
            git diff --cached
            ;;
        3)
            git log --oneline -n 10
            echo ""
            read -p "请输入第一个 commit ID: " commit1
            read -p "请输入第二个 commit ID: " commit2
            git diff "$commit1" "$commit2"
            ;;
        *)
            print_error "无效选择"
            ;;
    esac

    echo ""
    read -p "按回车继续..."
}

# 12. 查看当前状态
view_status() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  当前状态"
    echo "=========================================="
    echo ""

    git status

    echo ""
    read -p "按回车继续..."
}

# 13. 查看修改内容
view_changes() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  修改内容"
    echo "=========================================="
    echo ""

    git diff

    echo ""
    read -p "按回车继续..."
}

# 14. 查看文件修改历史
view_file_history() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  文件修改历史"
    echo "=========================================="
    echo ""

    read -p "请输入文件路径: " filepath

    if [ ! -f "$filepath" ]; then
        print_error "文件不存在: $filepath"
        read -p "按回车继续..."
        return
    fi

    echo ""
    git log --oneline -- "$filepath"
    echo ""

    read -p "是否查看详细修改? (y/n): " show_details

    if [ "$show_details" = "y" ]; then
        git log -p -- "$filepath"
    fi

    echo ""
    read -p "按回车继续..."
}

# 15. 创建新分支
create_branch() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  创建新分支"
    echo "=========================================="
    echo ""

    echo "当前分支:"
    git branch
    echo ""

    read -p "请输入新分支名称: " branch_name

    if [ -z "$branch_name" ]; then
        print_error "未输入分支名称"
        read -p "按回车继续..."
        return
    fi

    git checkout -b "$branch_name"

    if [ $? -eq 0 ]; then
        print_success "已创建并切换到分支: $branch_name"

        read -p "是否立即推送到 GitHub? (y/n): " push_now

        if [ "$push_now" = "y" ]; then
            git push -u origin "$branch_name"
            print_success "已推送"
        fi
    else
        print_error "创建分支失败"
    fi

    read -p "按回车继续..."
}

# 16. 切换分支
switch_branch() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  切换分支"
    echo "=========================================="
    echo ""

    echo "所有分支:"
    git branch -a
    echo ""

    read -p "请输入要切换到的分支名称: " branch_name

    if [ -z "$branch_name" ]; then
        print_error "未输入分支名称"
        read -p "按回车继续..."
        return
    fi

    git checkout "$branch_name"

    if [ $? -eq 0 ]; then
        print_success "已切换到分支: $branch_name"
    else
        print_error "切换分支失败"
    fi

    read -p "按回车继续..."
}

# 17. 合并分支
merge_branch() {
    if ! check_git_repo; then return; fi

    echo ""
    echo "=========================================="
    echo "  合并分支"
    echo "=========================================="
    echo ""

    echo "当前分支:"
    current_branch=$(git branch --show-current)
    echo "  $current_branch"
    echo ""

    echo "所有分支:"
    git branch
    echo ""

    read -p "请输入要合并的分支名称: " branch_name

    if [ -z "$branch_name" ]; then
        print_error "未输入分支名称"
        read -p "按回车继续..."
        return
    fi

    print_warning "将 $branch_name 合并到 $current_branch"
    read -p "确定继续? (y/n): " confirm

    if [ "$confirm" != "y" ]; then
        print_info "已取消"
        read -p "按回车继续..."
        return
    fi

    git merge "$branch_name"

    if [ $? -eq 0 ]; then
        print_success "合并成功!"

        read -p "是否推送到 GitHub? (y/n): " push_now

        if [ "$push_now" = "y" ]; then
            git push
            print_success "已推送"
        fi
    else
        print_error "合并失败，可能存在冲突"
        print_info "请手动解决冲突后执行:"
        echo "  git add ."
        echo "  git commit"
        echo "  git push"
    fi

    read -p "按回车继续..."
}

# 18. 配置用户信息
config_user() {
    echo ""
    echo "=========================================="
    echo "  配置用户信息"
    echo "=========================================="
    echo ""

    read -p "请输入用户名 (默认: ${GITHUB_USER}): " username
    read -p "请输入邮箱: " email

    if [ -z "$username" ]; then
        username="${GITHUB_USER}"
    fi

    if [ -z "$email" ]; then
        print_error "邮箱不能为空"
        read -p "按回车继续..."
        return
    fi

    git config --global user.name "$username"
    git config --global user.email "$email"

    print_success "配置成功!"
    echo ""
    echo "用户名: $username"
    echo "邮箱: $email"

    read -p "按回车继续..."
}

# 19. 配置 Token/SSH
config_credentials() {
    echo ""
    echo "=========================================="
    echo "  配置认证信息"
    echo "=========================================="
    echo ""

    echo "请选择认证方式:"
    echo "1. Personal Access Token (推荐)"
    echo "2. SSH 密钥"
    echo ""

    read -p "请选择 (1/2): " choice

    case $choice in
        1)
            print_info "使用 Personal Access Token"
            echo ""
            print_info "获取 Token 步骤:"
            echo "  1. 访问: https://github.com/settings/tokens"
            echo "  2. Generate new token (classic)"
            echo "  3. 勾选 'repo' 权限"
            echo "  4. 复制生成的 Token"
            echo ""

            read -p "请输入 Token: " token

            if [ -z "$token" ]; then
                print_error "Token 不能为空"
                read -p "按回车继续..."
                return
            fi

            # 保存凭据
            git config --global credential.helper store

            # 设置远程 URL
            if check_git_repo; then
                git remote set-url origin "https://${token}@github.com/${GITHUB_USER}/${REPO_NAME}.git"
                print_success "Token 已配置"
            else
                print_info "Token 将在下次推送时使用"
            fi
            ;;

        2)
            print_info "配置 SSH 密钥"
            echo ""

            if [ -f ~/.ssh/id_ed25519.pub ]; then
                print_info "SSH 密钥已存在:"
                cat ~/.ssh/id_ed25519.pub
                echo ""
            else
                print_info "生成新的 SSH 密钥..."
                read -p "请输入邮箱: " email
                ssh-keygen -t ed25519 -C "$email"
                print_success "密钥已生成"
                echo ""
                print_info "公钥内容:"
                cat ~/.ssh/id_ed25519.pub
                echo ""
            fi

            print_info "请将上面的公钥添加到 GitHub:"
            echo "  1. 访问: https://github.com/settings/keys"
            echo "  2. New SSH key"
            echo "  3. 粘贴公钥"
            echo ""

            read -p "完成后按回车继续..."

            # 设置远程 URL 为 SSH
            if check_git_repo; then
                git remote set-url origin "git@github.com:${GITHUB_USER}/${REPO_NAME}.git"
                print_success "已切换到 SSH"

                print_info "测试连接..."
                ssh -T git@github.com
            fi
            ;;

        *)
            print_error "无效选择"
            ;;
    esac

    read -p "按回车继续..."
}

# 20. 查看配置信息
view_config() {
    echo ""
    echo "=========================================="
    echo "  配置信息"
    echo "=========================================="
    echo ""

    echo "用户配置:"
    git config --global user.name 2>/dev/null && echo "  用户名: $(git config --global user.name)" || echo "  用户名: 未配置"
    git config --global user.email 2>/dev/null && echo "  邮箱: $(git config --global user.email)" || echo "  邮箱: 未配置"
    echo ""

    if check_git_repo; then
        echo "当前仓库:"
        echo "  远程地址: $(git remote get-url origin 2>/dev/null || echo '未配置')"
        echo "  当前分支: $(git branch --show-current 2>/dev/null || echo '无')"
        echo ""

        echo "远程仓库:"
        git remote -v
    fi

    echo ""
    read -p "按回车继续..."
}

# 主循环
main() {
    while true; do
        show_menu
        read -p "请选择操作 (0-20): " choice

        case $choice in
            1) init_and_upload ;;
            2) quick_commit ;;
            3) commit_specific_file ;;
            4) commit_multiple_files ;;
            5) clone_repo ;;
            6) pull_latest ;;
            7) timestamped_commit ;;
            8) view_history ;;
            9) rollback_previous ;;
            10) rollback_specific ;;
            11) view_diff ;;
            12) view_status ;;
            13) view_changes ;;
            14) view_file_history ;;
            15) create_branch ;;
            16) switch_branch ;;
            17) merge_branch ;;
            18) config_user ;;
            19) config_credentials ;;
            20) view_config ;;
            0)
                echo ""
                print_info "再见! 豌豆炮，不爽就开炮!"
                echo ""
                exit 0
                ;;
            *)
                print_error "无效选择，请重试"
                sleep 2
                ;;
        esac
    done
}

# 运行主程序
main
