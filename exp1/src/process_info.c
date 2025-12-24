/**
 * @file process_info.c
 * @brief 进程运行信息获取实现（彩色版本）
 * 
 * 使用popen执行ps命令获取进程信息
 */

#include <stdio.h>
#include <stdlib.h>
#include "process_info.h"
#include "logger.h"
#include "colors.h"

#define BUFFER_SIZE 512

/**
 * @brief 显示进程运行信息
 * 使用ps命令获取进程信息
 */
void show_process_info(void)
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    int line_count = 0;
    
    printf("\n" BOLD_BLUE "┌─────────────────────────────────────┐\n");
    printf("│          " BOLD_WHITE "进程运行信息" BOLD_BLUE "                 │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("--- 进程运行信息 ---\n");
    
    /* 使用ps命令获取进程信息 */
    fp = popen("ps aux --sort=-%mem | head -20", "r");
    if (fp == NULL) {
        printf(BOLD_RED "错误：无法执行ps命令\n" RESET);
        log_info("错误：无法执行ps命令\n");
        return;
    }
    
    printf(BOLD_YELLOW "★ 前20个内存占用最高的进程:\n\n" RESET);
    log_info("前20个内存占用最高的进程:\n");
    
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        if (line_count == 0) {
            /* 标题行使用特殊颜色 */
            printf(BOLD_CYAN "%s" RESET, buffer);
        } else {
            /* 数据行交替颜色 */
            if (line_count % 2 == 0) {
                printf(GREEN "%s" RESET, buffer);
            } else {
                printf(WHITE "%s" RESET, buffer);
            }
        }
        log_info(buffer);
        line_count++;
    }
    
    pclose(fp);
    
    /* 显示进程统计信息 */
    printf("\n" BOLD_GREEN "┌───── 进程统计信息 ────┐\n" RESET);
    log_info("\n--- 进程统计信息 ---\n");
    
    fp = popen("ps aux | wc -l", "r");
    if (fp != NULL) {
        if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            int total = atoi(buffer) - 1; /* 减去标题行 */
            printf(BOLD_WHITE "│ " BOLD_YELLOW "当前运行进程总数: " BOLD_GREEN "%d" BOLD_WHITE " │\n" RESET, total);
            printf(BOLD_GREEN "└───────────────────────┘\n" RESET);
            snprintf(buffer, BUFFER_SIZE, "当前运行进程总数: %d\n", total);
            log_info(buffer);
        }
        pclose(fp);
    }
}
