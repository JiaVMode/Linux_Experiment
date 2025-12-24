/**
 * @file memory_info.h
 * @brief 内存硬件信息和使用信息获取头文件
 */

#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H

/**
 * @brief 显示内存硬件信息和使用信息
 * 读取/proc/meminfo获取内存信息
 */
void show_memory_info(void);

#endif /* MEMORY_INFO_H */
