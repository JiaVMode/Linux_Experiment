/**
 * @file menu.c
 * @brief 菜单显示和用户输入处理实现（彩色版本）
 */

#include <stdio.h>
#include <ctype.h>
#include "menu.h"
#include "colors.h"
#include "cpu_info.h"
#include "process_info.h"
#include "memory_info.h"
#include "storage_info.h"
#include "logger.h"

/**
 * @brief 显示主菜单（彩色版本）
 */
void display_menu(void)
{
    printf("\n");
    printf(BOLD_CYAN "------------------\n" RESET);
    printf(BOLD_GREEN "C\t\t" BOLD_YELLOW "交互菜单\n" RESET);
    printf(BOLD_CYAN "------------------\n" RESET);
    printf(BOLD_RED "A" RESET ":" CYAN "查看CPU硬件信息\n" RESET);
    printf(BOLD_RED "B" RESET ":" CYAN "查看进程运行信息\n" RESET);
    printf(BOLD_RED "C" RESET ":" CYAN "查看内存硬件信息、内存使用信息\n" RESET);
    printf(BOLD_RED "D" RESET ":" CYAN "查看存储设备硬件信息、存储设备使用信息\n" RESET);
    printf(BOLD_RED "E" RESET ":" YELLOW "退出\n" RESET);
    printf(BOLD_CYAN "------------------\n" RESET);
    printf(BOLD_WHITE "请输入选项: " RESET);
}

/**
 * @brief 获取用户输入选项
 * @return 用户输入的选项字符（转换为大写）
 */
char get_user_choice(void)
{
    char choice;
    int c;
    
    choice = getchar();
    /* 清除输入缓冲区 */
    while ((c = getchar()) != '\n' && c != EOF);
    
    return toupper(choice);
}

/**
 * @brief 处理用户选择
 * @param choice 用户选择的选项
 * @return 0表示继续运行，1表示退出
 */
int handle_choice(char choice)
{
    switch (choice) {
        case 'A':
            printf("\n" BOLD_GREEN ">>> " BOLD_YELLOW "查看CPU硬件信息" BOLD_GREEN " <<<\n" RESET);
            log_info("=== 查看CPU硬件信息 ===\n");
            show_cpu_info();
            break;
        case 'B':
            printf("\n" BOLD_GREEN ">>> " BOLD_YELLOW "查看进程运行信息" BOLD_GREEN " <<<\n" RESET);
            log_info("=== 查看进程运行信息 ===\n");
            show_process_info();
            break;
        case 'C':
            printf("\n" BOLD_GREEN ">>> " BOLD_YELLOW "查看内存硬件信息、内存使用信息" BOLD_GREEN " <<<\n" RESET);
            log_info("=== 查看内存硬件信息、内存使用信息 ===\n");
            show_memory_info();
            break;
        case 'D':
            printf("\n" BOLD_GREEN ">>> " BOLD_YELLOW "查看存储设备硬件信息、存储设备使用信息" BOLD_GREEN " <<<\n" RESET);
            log_info("=== 查看存储设备硬件信息、存储设备使用信息 ===\n");
            show_storage_info();
            break;
        case 'E':
            log_info("=== 用户选择退出程序 ===\n");
            return 1;
        default:
            printf("\n" BOLD_RED "无效选项，请重新输入！\n" RESET);
            log_info("用户输入无效选项\n");
            break;
    }
    return 0;
}
