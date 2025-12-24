/**
 * @file storage_info.c
 * @brief 存储设备硬件信息和使用信息获取实现（彩色版本）
 * 
 * 通过读取/proc/partitions和使用df、lsblk命令获取存储信息
 */

#include <stdio.h>
#include <string.h>
#include "storage_info.h"
#include "logger.h"
#include "colors.h"

#define BUFFER_SIZE 512

/**
 * @brief 显示存储设备硬件信息和使用信息
 * 使用df命令和读取/proc/partitions
 */
void show_storage_info(void)
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    int line_count = 0;
    
    /* 显示磁盘分区信息 */
    printf("\n" BOLD_RED "┌─────────────────────────────────────┐\n");
    printf("│        " BOLD_WHITE "存储设备硬件信息" BOLD_RED "             │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("--- 存储设备硬件信息 ---\n");
    
    printf(BOLD_YELLOW "★ 磁盘分区信息 (/proc/partitions):\n" RESET);
    log_info("磁盘分区信息 (/proc/partitions):\n");
    
    fp = fopen("/proc/partitions", "r");
    if (fp != NULL) {
        line_count = 0;
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            if (line_count < 2) {
                printf(BOLD_CYAN "%s" RESET, buffer);
            } else {
                printf(GREEN "%s" RESET, buffer);
            }
            log_info(buffer);
            line_count++;
        }
        fclose(fp);
    } else {
        printf(BOLD_RED "无法读取分区信息\n" RESET);
        log_info("无法读取分区信息\n");
    }
    
    /* 使用lsblk显示块设备信息 */
    printf("\n" BOLD_MAGENTA "★ 块设备信息 (lsblk):\n" RESET);
    log_info("\n块设备信息 (lsblk):\n");
    
    fp = popen("lsblk 2>/dev/null", "r");
    if (fp != NULL) {
        line_count = 0;
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            if (line_count == 0) {
                printf(BOLD_CYAN "%s" RESET, buffer);
            } else if (strstr(buffer, "disk") != NULL) {
                printf(BOLD_GREEN "%s" RESET, buffer);
            } else if (strstr(buffer, "part") != NULL) {
                printf(YELLOW "%s" RESET, buffer);
            } else {
                printf(WHITE "%s" RESET, buffer);
            }
            log_info(buffer);
            line_count++;
        }
        pclose(fp);
    }
    
    /* 显示磁盘使用情况 */
    printf("\n" BOLD_YELLOW "┌─────────────────────────────────────┐\n");
    printf("│        " BOLD_WHITE "存储设备使用信息" BOLD_YELLOW "             │\n");
    printf("└─────────────────────────────────────┘\n" RESET);
    log_info("\n--- 存储设备使用信息 ---\n");
    
    printf(BOLD_CYAN "★ 磁盘使用情况 (df -h):\n" RESET);
    log_info("磁盘使用情况 (df -h):\n");
    
    fp = popen("df -h", "r");
    if (fp != NULL) {
        line_count = 0;
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            if (line_count == 0) {
                printf(BOLD_WHITE "%s" RESET, buffer);
            } else {
                /* 根据使用率着色 */
                int usage = 0;
                char *percent = strstr(buffer, "%");
                if (percent != NULL && percent > buffer) {
                    char *start = percent - 1;
                    while (start > buffer && *start >= '0' && *start <= '9') {
                        start--;
                    }
                    usage = atoi(start + 1);
                }
                
                if (usage >= 90) {
                    printf(BOLD_RED "%s" RESET, buffer);  /* 危险：90%以上 */
                } else if (usage >= 70) {
                    printf(YELLOW "%s" RESET, buffer);    /* 警告：70-90% */
                } else {
                    printf(GREEN "%s" RESET, buffer);     /* 正常：70%以下 */
                }
            }
            log_info(buffer);
            line_count++;
        }
        pclose(fp);
    } else {
        printf(BOLD_RED "错误：无法执行df命令\n" RESET);
        log_info("错误：无法执行df命令\n");
    }
    
    /* 显示使用率图例 */
    printf("\n" BOLD_WHITE "图例: " GREEN "■ 正常(<70%%)" RESET " " YELLOW "■ 警告(70-90%%)" RESET " " BOLD_RED "■ 危险(>90%%)\n" RESET);
}
