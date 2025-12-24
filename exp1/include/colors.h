/**
 * @file colors.h
 * @brief 终端颜色定义头文件
 * 
 * 使用ANSI转义码实现终端彩色输出
 */

#ifndef COLORS_H
#define COLORS_H

/* 重置所有属性 */
#define RESET       "\033[0m"

/* 常规颜色 */
#define BLACK       "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"

/* 粗体颜色 */
#define BOLD_BLACK      "\033[1;30m"
#define BOLD_RED        "\033[1;31m"
#define BOLD_GREEN      "\033[1;32m"
#define BOLD_YELLOW     "\033[1;33m"
#define BOLD_BLUE       "\033[1;34m"
#define BOLD_MAGENTA    "\033[1;35m"
#define BOLD_CYAN       "\033[1;36m"
#define BOLD_WHITE      "\033[1;37m"

/* 背景颜色 */
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

/* 特殊样式 */
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"

#endif /* COLORS_H */
