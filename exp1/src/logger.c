/**
 * @file logger.c
 * @brief 日志记录功能实现
 * 
 * 将用户输入选项与显示信息写入log.txt文件
 */

#include <stdio.h>
#include <time.h>
#include "logger.h"

/* 日志文件指针 */
static FILE *log_file = NULL;

/**
 * @brief 获取当前时间字符串
 * @param buffer 存储时间字符串的缓冲区
 * @param size 缓冲区大小
 */
static void get_time_string(char *buffer, size_t size)
{
    time_t now;
    struct tm *tm_info;
    
    time(&now);
    tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

/**
 * @brief 初始化日志文件
 * @return 0表示成功，-1表示失败
 */
int init_logger(void)
{
    char time_str[64];
    
    log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        return -1;
    }
    
    get_time_string(time_str, sizeof(time_str));
    fprintf(log_file, "\n========================================\n");
    fprintf(log_file, "程序启动时间: %s\n", time_str);
    fprintf(log_file, "========================================\n");
    fflush(log_file);
    
    return 0;
}

/**
 * @brief 关闭日志文件
 */
void close_logger(void)
{
    char time_str[64];
    
    if (log_file != NULL) {
        get_time_string(time_str, sizeof(time_str));
        fprintf(log_file, "\n程序结束时间: %s\n", time_str);
        fprintf(log_file, "========================================\n");
        fclose(log_file);
        log_file = NULL;
    }
}

/**
 * @brief 记录用户选项到日志
 * @param choice 用户选择的选项
 */
void log_choice(char choice)
{
    char time_str[64];
    
    if (log_file != NULL) {
        get_time_string(time_str, sizeof(time_str));
        fprintf(log_file, "[%s] 用户选择: %c\n", time_str, choice);
        fflush(log_file);
    }
}

/**
 * @brief 记录信息到日志
 * @param info 要记录的信息
 */
void log_info(const char *info)
{
    if (log_file != NULL && info != NULL) {
        fprintf(log_file, "%s", info);
        fflush(log_file);
    }
}
