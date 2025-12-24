/**
 * @file logger.h
 * @brief 日志记录功能头文件
 */

#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief 初始化日志文件
 * @return 0表示成功，-1表示失败
 */
int init_logger(void);

/**
 * @brief 关闭日志文件
 */
void close_logger(void);

/**
 * @brief 记录用户选项到日志
 * @param choice 用户选择的选项
 */
void log_choice(char choice);

/**
 * @brief 记录信息到日志
 * @param info 要记录的信息
 */
void log_info(const char *info);

#endif /* LOGGER_H */
