/**
 * @file storage_info.h
 * @brief 存储设备硬件信息和使用信息获取头文件
 */

#ifndef STORAGE_INFO_H
#define STORAGE_INFO_H

/**
 * @brief 显示存储设备硬件信息和使用信息
 * 使用df命令和读取/proc/partitions
 */
void show_storage_info(void);

#endif /* STORAGE_INFO_H */
