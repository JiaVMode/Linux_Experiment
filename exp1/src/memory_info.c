/**
 * @file memory_info.c
 * @brief 内存硬件信息和使用信息获取实现（彩色版本）
 * 
 * 通过读取/proc/meminfo和使用free命令获取内存信息
 */

#include <stdio.h>
#include <string.h>
#include "memory_info.h"
#include "logger.h"
#include "colors.h"

#define BUFFER_SIZE 256

/**
 * @brief 显示内存硬件信息和使用信息
 * 读取/proc/meminfo获取内存信息
 */
void show_memory_info(void)
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char log_buffer[BUFFER_SIZE * 2];
    
    printf("\n" BOLD_GREEN "┌─────────────────────────────────────┐\n");
    printf("│          " BOLD_WHITE "内存硬件信息" BOLD_GREEN "                 │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("--- 内存硬件信息 ---\n");
    
    /* 读取/proc/meminfo */
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        printf(BOLD_RED "错误：无法读取内存信息\n" RESET);
        log_info("错误：无法读取/proc/meminfo\n");
        return;
    }
    
    /* 只显示关键内存信息 */
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        if (strncmp(buffer, "MemTotal", 8) == 0) {
            printf(BOLD_CYAN "● " BOLD_YELLOW "总内存      " WHITE "%s" RESET, buffer + 9);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "MemFree", 7) == 0) {
            printf(BOLD_CYAN "● " BOLD_GREEN "空闲内存    " WHITE "%s" RESET, buffer + 8);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "MemAvailable", 12) == 0) {
            printf(BOLD_CYAN "● " BOLD_GREEN "可用内存    " WHITE "%s" RESET, buffer + 13);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "Buffers", 7) == 0) {
            printf(BOLD_CYAN "● " MAGENTA "缓冲区      " WHITE "%s" RESET, buffer + 8);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "Cached", 6) == 0 && buffer[6] == ':') {
            printf(BOLD_CYAN "● " MAGENTA "缓存        " WHITE "%s" RESET, buffer + 7);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "SwapTotal", 9) == 0) {
            printf(BOLD_CYAN "● " YELLOW "交换区总量  " WHITE "%s" RESET, buffer + 10);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "SwapFree", 8) == 0) {
            printf(BOLD_CYAN "● " YELLOW "交换区空闲  " WHITE "%s" RESET, buffer + 9);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        }
    }
    fclose(fp);
    
    /* 使用free命令显示更直观的内存使用情况 */
    printf("\n" BOLD_YELLOW "┌─────────────────────────────────────┐\n");
    printf("│        " BOLD_WHITE "内存使用信息 (free -h)" BOLD_YELLOW "       │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("\n--- 内存使用信息 (free -h) ---\n");
    
    fp = popen("free -h", "r");
    if (fp != NULL) {
        int line = 0;
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            if (line == 0) {
                printf(BOLD_CYAN "%s" RESET, buffer);
            } else if (line == 1) {
                printf(BOLD_GREEN "%s" RESET, buffer);
            } else {
                printf(YELLOW "%s" RESET, buffer);
            }
            log_info(buffer);
            line++;
        }
        pclose(fp);
    }
}
