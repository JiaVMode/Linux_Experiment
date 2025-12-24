/**
 * @file menu.h
 * @brief 菜单显示和用户输入处理头文件
 */

#ifndef MENU_H
#define MENU_H

/**
 * @brief 显示主菜单
 */
void display_menu(void);

/**
 * @brief 获取用户输入选项
 * @return 用户输入的选项字符
 */
char get_user_choice(void);

/**
 * @brief 处理用户选择
 * @param choice 用户选择的选项
 * @return 0表示继续运行，1表示退出
 */
int handle_choice(char choice);

#endif /* MENU_H */
