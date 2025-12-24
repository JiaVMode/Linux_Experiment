/**
 * @file cpu_info.c
 * @brief CPU硬件信息获取实现（彩色版本）
 * 
 * 通过读取/proc/cpuinfo获取CPU详细信息
 */

#include <stdio.h>
#include <string.h>
#include "cpu_info.h"
#include "logger.h"
#include "colors.h"

#define BUFFER_SIZE 256

/**
 * @brief 显示CPU硬件信息
 * 读取/proc/cpuinfo获取CPU信息
 */
void show_cpu_info(void)
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char log_buffer[BUFFER_SIZE * 2];
    int processor_count = 0;
    
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf(BOLD_RED "错误：无法读取CPU信息\n" RESET);
        log_info("错误：无法读取/proc/cpuinfo\n");
        return;
    }
    
    printf("\n" BOLD_MAGENTA "┌─────────────────────────────────────┐\n");
    printf("│          " BOLD_WHITE "CPU硬件信息" BOLD_MAGENTA "                │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("--- CPU硬件信息 ---\n");
    
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        /* 显示关键CPU信息 */
        if (strncmp(buffer, "processor", 9) == 0) {
            processor_count++;
            printf(BOLD_CYAN "● " GREEN "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "model name", 10) == 0) {
            printf(BOLD_CYAN "● " YELLOW "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "cpu MHz", 7) == 0) {
            printf(BOLD_CYAN "● " CYAN "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "cache size", 10) == 0) {
            printf(BOLD_CYAN "● " MAGENTA "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "cpu cores", 9) == 0) {
            printf(BOLD_CYAN "● " GREEN "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        } else if (strncmp(buffer, "vendor_id", 9) == 0) {
            printf(BOLD_CYAN "● " WHITE "%s" RESET, buffer);
            snprintf(log_buffer, sizeof(log_buffer), "%s", buffer);
            log_info(log_buffer);
        }
    }
    
    printf("\n" BOLD_GREEN "★ 总处理器数量: " BOLD_YELLOW "%d\n" RESET, processor_count);
    snprintf(log_buffer, sizeof(log_buffer), "总处理器数量: %d\n", processor_count);
    log_info(log_buffer);
    
    fclose(fp);
}
