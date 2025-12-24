# 实验二：Shell脚本交互式菜单程序

## 一、实验目的

掌握Shell脚本的基本语法和编程技巧，学习使用Linux系统命令获取系统信息，掌握Shell脚本中的条件判断和循环结构，了解函数的定义和使用方法，以及学习使用ANSI转义码实现终端彩色输出。

## 二、实验环境

- 操作系统：Linux
- Shell类型：Bash

## 三、设计思路

本程序采用模块化函数设计，将不同功能封装到独立的函数中，主要包括：show_welcome()显示欢迎界面、show_header()显示带日期的菜单头部、show_menu()显示彩色菜单选项、print_box_header()打印带边框的标题、print_line()打印分隔线，以及四个信息显示函数show_process_info()、show_user_info()、show_directory_info()、show_system_info()分别负责显示进程、用户、目录和系统信息。main()函数作为主程序实现菜单循环。

在系统信息获取方面，程序使用多种Linux命令：date命令获取系统日期并格式化为"年/月/日"格式；ps aux命令显示所有进程信息；whoami、who、id、groups等命令获取用户相关信息；pwd和ls -la显示当前目录路径和内容；hostname获取计算机名、uname -r获取内核版本、hostname -I和ip addr获取IP地址信息。

为增强用户体验，程序使用ANSI转义码实现终端彩色输出。颜色定义在脚本开头，使用\033[转义序列。菜单采用双线边框字符（╔═╗╚╝║）构建精美外观，边框使用青色，选项字母使用红色突出显示，退出选项使用黄色。在目录内容显示中，目录项使用蓝色、可执行文件使用绿色、普通文件使用白色，实现类似ls --color的效果。各模块标题使用不同颜色的星号（★）作为前缀，增加视觉层次感。

程序主循环使用while true实现无限循环，通过case语句判断用户输入并调用相应函数，用户选择E时调用exit 0退出。输入处理使用tr命令将小写字母转换为大写，使程序对大小写输入不敏感。

## 四、源代码（含注释）

```bash
#!/bin/bash
#====================================================
# 脚本名称: menu.sh
# 功能描述: Linux系统信息查询交互式菜单（彩色版本）
#====================================================

#----------------------------------------------------
# 颜色定义 - 使用ANSI转义码
#----------------------------------------------------
RESET='\033[0m'           # 重置所有属性
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
BOLD_RED='\033[1;31m'
BOLD_GREEN='\033[1;32m'
BOLD_YELLOW='\033[1;33m'
BOLD_BLUE='\033[1;34m'
BOLD_MAGENTA='\033[1;35m'
BOLD_CYAN='\033[1;36m'
BOLD_WHITE='\033[1;37m'

# 打印彩色分隔线
print_line() {
    echo -e "${BOLD_CYAN}────────────────────────────────────────────────${RESET}"
}

# 打印带边框的彩色标题
print_box_header() {
    local title="$1"
    echo ""
    echo -e "${BOLD_GREEN}┌────────────────────────────────────────────────┐${RESET}"
    echo -e "${BOLD_GREEN}│${BOLD_WHITE}                $title                        ${BOLD_GREEN}│${RESET}"
    echo -e "${BOLD_GREEN}└────────────────────────────────────────────────┘${RESET}"
    echo ""
}

# 显示菜单头部（包含系统名称和日期）
show_header() {
    current_date=$(date +"%y/%m/%d")
    echo ""
    echo -e "${BOLD_CYAN}╔════════════════════════════════════════════════╗${RESET}"
    echo -e "${BOLD_CYAN}║${BOLD_GREEN}  Linux${RESET}                               ${BOLD_YELLOW}$current_date${BOLD_CYAN}  ║${RESET}"
    echo -e "${BOLD_CYAN}╠════════════════════════════════════════════════╣${RESET}"
}

# 显示彩色菜单选项
show_menu() {
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}A${RESET}:${CYAN}查看进程信息${RESET}                                 ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}B${RESET}:${CYAN}查看用户信息${RESET}                                 ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}C${RESET}:${CYAN}显示当前目录信息${RESET}                             ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}D${RESET}:${CYAN}显示计算机名、内核版本、IP地址${RESET}               ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}║${RESET} ${BOLD_RED}E${RESET}:${YELLOW}退出${RESET}                                         ${BOLD_CYAN}║${RESET}"
    echo -e "${BOLD_CYAN}╚════════════════════════════════════════════════╝${RESET}"
}

# 显示进程信息
show_process_info() {
    print_box_header "进程信息"
    echo -e "${BOLD_YELLOW}★ 当前用户进程${RESET}"
    print_line
    ps aux | head -1 | while read line; do echo -e "${BOLD_CYAN}$line${RESET}"; done
    ps aux | tail -n +2 | head -14 | while IFS= read -r line; do echo -e "${GREEN}$line${RESET}"; done
    echo ""
    echo -e "${BOLD_MAGENTA}★ 进程统计${RESET}"
    print_line
    process_count=$(ps aux | wc -l)
    echo -e "${BOLD_WHITE}当前运行进程总数: ${BOLD_GREEN}$((process_count - 1))${RESET}"
}

# 显示用户信息
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
    who | while IFS= read -r line; do echo -e "${GREEN}$line${RESET}"; done
}

# 显示当前目录信息（目录蓝色、可执行文件绿色）
show_directory_info() {
    print_box_header "目录信息"
    echo -e "${BOLD_YELLOW}★ 当前工作目录${RESET}"
    print_line
    echo -e "${BOLD_GREEN}$(pwd)${RESET}"
    echo ""
    echo -e "${BOLD_MAGENTA}★ 目录内容${RESET}"
    print_line
    ls -la | while IFS= read -r line; do
        if [[ "$line" == d* ]]; then echo -e "${BOLD_BLUE}$line${RESET}"
        elif [[ "$line" == -* && "$line" == *x* ]]; then echo -e "${BOLD_GREEN}$line${RESET}"
        else echo -e "${WHITE}$line${RESET}"; fi
    done
}

# 显示系统信息
show_system_info() {
    print_box_header "系统信息"
    echo -e "${BOLD_YELLOW}★ 计算机名${RESET}"
    print_line
    echo -e "${BOLD_GREEN}$(hostname)${RESET}"
    echo ""
    echo -e "${BOLD_MAGENTA}★ Linux内核版本${RESET}"
    print_line
    echo -e "${BOLD_CYAN}● ${RESET}内核版本: ${BOLD_YELLOW}$(uname -r)${RESET}"
    echo ""
    echo -e "${BOLD_BLUE}★ 当前IP地址${RESET}"
    print_line
    ip_addr=$(hostname -I 2>/dev/null)
    echo -e "${BOLD_CYAN}● ${RESET}IP地址: ${BOLD_GREEN}$ip_addr${RESET}"
}

# 主程序循环
main() {
    clear
    while true; do
        show_header
        show_menu
        echo -n -e "${BOLD_WHITE}请输入选项: ${RESET}"
        read choice
        choice=$(echo "$choice" | tr 'a-z' 'A-Z')
        case $choice in
            A) show_process_info ;;
            B) show_user_info ;;
            C) show_directory_info ;;
            D) show_system_info ;;
            E) echo -e "${BOLD_GREEN}✓ ${BOLD_YELLOW}感谢使用，再见！${RESET}"; exit 0 ;;
            *) echo -e "${BOLD_RED}✗ 无效选项！${RESET}" ;;
        esac
        echo -n -e "${BOLD_WHITE}按回车键继续...${RESET}"; read dummy
    done
}
main
```

## 五、运行方法

```bash
chmod +x menu.sh
./menu.sh
```

## 六、运行结果

### 6.1 主菜单

```
╔════════════════════════════════════════════════╗
║  Linux                               24/12/24  ║
╠════════════════════════════════════════════════╣
║ A:查看进程信息                                 ║
║ B:查看用户信息                                 ║
║ C:显示当前目录信息                             ║
║ D:显示计算机名、内核版本、IP地址               ║
║ E:退出                                         ║
╚════════════════════════════════════════════════╝
请输入选项: 
```

### 6.2 进程信息

```
┌────────────────────────────────────────────────┐
│                进程信息                        │
└────────────────────────────────────────────────┘

★ 当前用户进程
────────────────────────────────────────────────
USER   PID %CPU %MEM    VSZ   RSS TTY   STAT START TIME COMMAND
root     1  0.0  0.1 169936 11892 ?     Ss   10:00 0:02 /sbin/init
...

★ 进程统计
────────────────────────────────────────────────
当前运行进程总数: 156
```

### 6.3 目录信息（彩色显示）

```
┌────────────────────────────────────────────────┐
│                目录信息                        │
└────────────────────────────────────────────────┘

★ 当前工作目录
────────────────────────────────────────────────
/home/user/exp2

★ 目录内容
────────────────────────────────────────────────
drwxr-xr-x 2 user user 4096 Dec 24 .         (蓝色)
drwxr-xr-x 4 user user 4096 Dec 24 ..        (蓝色)
-rwxr-xr-x 1 user user 5659 Dec 24 menu.sh   (绿色)
-rw-r--r-- 1 user user 8000 Dec 24 report2.md (白色)
```

## 七、总结

本实验完成了一个Shell脚本交互式菜单程序，实现了日期显示、进程信息查看、用户信息查看、目录信息显示、系统信息查询和彩色界面显示等功能。通过本实验，掌握了Shell脚本编程、Linux系统命令使用以及终端颜色控制等技能。
