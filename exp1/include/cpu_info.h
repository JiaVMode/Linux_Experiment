/**
 * @file cpu_info.h
 * @brief CPU硬件信息获取头文件
 */

#ifndef CPU_INFO_H
#define CPU_INFO_H

/**
 * @brief 显示CPU硬件信息
 * 读取/proc/cpuinfo获取CPU信息
 */
void show_cpu_info(void);

#endif /* CPU_INFO_H */
