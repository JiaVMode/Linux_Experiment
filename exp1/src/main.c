/**
 * @file main.c
 * @brief 主程序入口（彩色版本）
 * 
 * 实现命令行交互菜单的主循环
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "logger.h"
#include "colors.h"

/**
 * @brief 显示欢迎信息
 */
static void show_welcome(void)
{
    printf("\n");
    printf(BOLD_CYAN "╔════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD_CYAN "║" BOLD_YELLOW "                  Linux 系统信息查询工具                    " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "║" GREEN "                  System Information Tool                   " BOLD_CYAN "║\n" RESET);
    printf(BOLD_CYAN "╚════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
}

/**
 * @brief 主函数
 * 初始化日志，显示菜单，处理用户输入
 */
int main(void)
{
    char choice;
    int exit_flag = 0;
    
    /* 显示欢迎信息 */
    show_welcome();
    
    /* 初始化日志系统 */
    if (init_logger() != 0) {
        fprintf(stderr, BOLD_RED "警告：无法初始化日志文件\n" RESET);
    } else {
        printf(BOLD_GREEN "✓ " RESET "日志系统初始化成功\n");
    }
    
    /* 主循环 */
    while (!exit_flag) {
        display_menu();
        choice = get_user_choice();
        log_choice(choice);
        exit_flag = handle_choice(choice);
    }
    
    /* 关闭日志 */
    close_logger();
    
    printf("\n" BOLD_GREEN "✓ " BOLD_YELLOW "程序已退出，感谢使用！\n" RESET);
    return 0;
}
