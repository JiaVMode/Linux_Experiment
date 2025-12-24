#!/bin/bash
#====================================================
# 脚本名称: menu.sh
# 功能描述: Linux系统信息查询交互式菜单（彩色版本）
# 作者: 李嘉
# 日期: 2024-12-24
#====================================================

#----------------------------------------------------
# 颜色定义
#----------------------------------------------------
RESET='\033[0m'

# 常规颜色
BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'

# 粗体颜色
BOLD_BLACK='\033[1;30m'
BOLD_RED='\033[1;31m'
BOLD_GREEN='\033[1;32m'
BOLD_YELLOW='\033[1;33m'
BOLD_BLUE='\033[1;34m'
BOLD_MAGENTA='\033[1;35m'
BOLD_CYAN='\033[1;36m'
BOLD_WHITE='\033[1;37m'

#----------------------------------------------------
# 函数: print_line
# 功能: 打印分隔线
#----------------------------------------------------
print_line() {
    echo -e "${BOLD_CYAN}────────────────────────────────────────────────${RESET}"
}

#----------------------------------------------------
# 函数: print_box_header
# 功能: 打印带边框的标题
# 参数: $1 - 标题文字
#----------------------------------------------------
print_box_header() {
    local title="$1"
    echo ""
    echo -e "${BOLD_GREEN}┌────────────────────────────────────────────────┐${RESET}"
    echo -e "${BOLD_GREEN}│${BOLD_WHITE}                $title                        ${BOLD_GREEN}│${RESET}"
    echo -e "${BOLD_GREEN}└────────────────────────────────────────────────┘${RESET}"
    echo ""
}

#----------------------------------------------------
# 函数: show_header
# 功能: 显示菜单头部（包含系统名称和日期）
#----------------------------------------------------
show_header() {
    current_date=$(date +"%y/%m/%d")
    
    echo ""
    echo -e "${BOLD_CYAN}╔════════════════════════════════════════════════╗${RESET}"
    echo -e "${BOLD_CYAN}║${BOLD_GREEN}  Linux${RESET}                               ${BOLD_YELLOW}$current_date${BOLD_CYAN}  ║${RESET}"
    echo -e "${BOLD_CYAN}╠════════════════════════════════════════════════╣${RESET}"
}

#----------------------------------------------------
# 函数: show_menu
# 功能: 显示菜单选项（彩色版本）
#----------------------------------------------------
show_menu() {
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}A${RESET}:${CYAN}查看进程信息${RESET}                                 ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}B${RESET}:${CYAN}查看用户信息${RESET}                                 ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}C${RESET}:${CYAN}显示当前目录信息${RESET}                             ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}D${RESET}:${CYAN}显示计算机名、内核版本、IP地址${RESET}               ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}E${RESET}:${YELLOW}退出${RESET}                                         ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}╚════════════════════════════════════════════════╝${RESET}"
}

#----------------------------------------------------
# 函数: show_process_info
# 功能: 显示进程信息（彩色版本）
#----------------------------------------------------
show_process_info() {
    print_box_header "进程信息"
    
    echo -e "${BOLD_YELLOW}★ 当前用户进程${RESET}"
    print_line
    ps aux | head -1 | while read line; do
        echo -e "${BOLD_CYAN}$line${RESET}"
    done
    ps aux | tail -n +2 | head -14 | while IFS= read -r line; do
        echo -e "${GREEN}$line${RESET}"
    done
    
    echo ""
    echo -e "${BOLD_MAGENTA}★ 进程统计${RESET}"
    print_line
    process_count=$(ps aux | wc -l)
    echo -e "${BOLD_WHITE}当前运行进程总数: ${BOLD_GREEN}$((process_count - 1))${RESET}"
    echo ""
}

#----------------------------------------------------
# 函数: show_user_info
# 功能: 显示用户信息（彩色版本）
#----------------------------------------------------
show_user_info() {
    print_box_header "用户信息"
    
    echo -e "${BOLD_YELLOW}★ 当前用户${RESET}"
    print_line
    echo -e "${BOLD_CYAN}● ${RESET}用户名: ${BOLD_GREEN}$(whoami)${RESET}"
    echo -e "${BOLD_CYAN}● ${RESET}用户ID: ${BOLD_YELLOW}$(id -u)${RESET}"
    echo -e "${BOLD_CYAN}● ${RESET}所属组: ${MAGENTA}$(groups)${RESET}"
    
    echo ""
    echo -e "${BOLD_MAGENTA}★ 当前登录的所有用户${RESET}"
    print_line
    who | while IFS= read -r line; do
        echo -e "${GREEN}$line${RESET}"
    done
    
    echo ""
    echo -e "${BOLD_BLUE}★ 用户登录历史 (最近5条)${RESET}"
    print_line
    last -5 2>/dev/null | while IFS= read -r line; do
        echo -e "${CYAN}$line${RESET}"
    done || echo -e "${RED}无法获取登录历史${RESET}"
    echo ""
}

#----------------------------------------------------
# 函数: show_directory_info
# 功能: 显示当前目录信息（彩色版本）
#----------------------------------------------------
show_directory_info() {
    print_box_header "目录信息"
    
    echo -e "${BOLD_YELLOW}★ 当前工作目录${RESET}"
    print_line
    echo -e "${BOLD_GREEN}$(pwd)${RESET}"
    
    echo ""
    echo -e "${BOLD_MAGENTA}★ 目录内容 (详细列表)${RESET}"
    print_line
    ls -la | head -1 | while IFS= read -r line; do
        echo -e "${BOLD_WHITE}$line${RESET}"
    done
    ls -la | tail -n +2 | while IFS= read -r line; do
        if [[ "$line" == d* ]]; then
            echo -e "${BOLD_BLUE}$line${RESET}"
        elif [[ "$line" == -* && "$line" == *x* ]]; then
            echo -e "${BOLD_GREEN}$line${RESET}"
        else
            echo -e "${WHITE}$line${RESET}"
        fi
    done
    
    echo ""
    echo -e "${BOLD_CYAN}★ 目录统计${RESET}"
    print_line
    file_count=$(ls -l | grep -c "^-")
    dir_count=$(ls -l | grep -c "^d")
    echo -e "${BOLD_WHITE}文件数量: ${BOLD_YELLOW}$file_count${RESET}"
    echo -e "${BOLD_WHITE}目录数量: ${BOLD_BLUE}$((dir_count - 1))${RESET}"
    echo ""
}

#----------------------------------------------------
# 函数: show_system_info
# 功能: 显示系统信息（彩色版本）
#----------------------------------------------------
show_system_info() {
    print_box_header "系统信息"
    
    echo -e "${BOLD_YELLOW}★ 计算机名${RESET}"
    print_line
    echo -e "${BOLD_GREEN}$(hostname)${RESET}"
    
    echo ""
    echo -e "${BOLD_MAGENTA}★ Linux内核版本${RESET}"
    print_line
    echo -e "${BOLD_CYAN}● ${RESET}内核版本: ${BOLD_YELLOW}$(uname -r)${RESET}"
    echo -e "${BOLD_CYAN}● ${RESET}完整信息: ${WHITE}$(uname -a)${RESET}"
    
    echo ""
    echo -e "${BOLD_BLUE}★ 当前IP地址${RESET}"
    print_line
    if command -v hostname &> /dev/null; then
        ip_addr=$(hostname -I 2>/dev/null)
        if [ -n "$ip_addr" ]; then
            echo -e "${BOLD_CYAN}● ${RESET}IP地址: ${BOLD_GREEN}$ip_addr${RESET}"
        fi
    fi
    
    if command -v ip &> /dev/null; then
        echo ""
        echo -e "${BOLD_RED}★ 网络接口详情${RESET}"
        print_line
        ip addr show | grep -E "inet |inet6 " | grep -v "127.0.0.1" | head -5 | while IFS= read -r line; do
            echo -e "${CYAN}$line${RESET}"
        done
    fi
    echo ""
}

#----------------------------------------------------
# 函数: show_welcome
# 功能: 显示欢迎信息
#----------------------------------------------------
show_welcome() {
    clear
    echo ""
    echo -e "${BOLD_CYAN}╔════════════════════════════════════════════════╗${RESET}"
    echo -e "${BOLD_CYAN}║${RESET}                                                ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${BOLD_YELLOW}      Linux 系统信息查询工具 (Shell版)          ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${GREEN}         System Information Tool                ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET}                                                ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}╚════════════════════════════════════════════════╝${RESET}"
    echo ""
}

#----------------------------------------------------
# 主程序
#----------------------------------------------------
main() {
    show_welcome
    
    while true; do
        show_header
        show_menu
        
        echo -n -e "${BOLD_WHITE}请输入选项: ${RESET}"
        read choice
        
        choice=$(echo "$choice" | tr 'a-z' 'A-Z')
        
        case $choice in
            A)
                show_process_info
                ;;
            B)
                show_user_info
                ;;
            C)
                show_directory_info
                ;;
            D)
                show_system_info
                ;;
            E)
                echo ""
                echo -e "${BOLD_GREEN}✓ ${BOLD_YELLOW}感谢使用，再见！${RESET}"
                echo ""
                exit 0
                ;;
            *)
                echo ""
                echo -e "${BOLD_RED}✗ 无效选项，请输入 A-E 之间的选项！${RESET}"
                echo ""
                ;;
        esac
        
        echo -n -e "${BOLD_WHITE}按回车键继续...${RESET}"
        read dummy
    done
}

main
