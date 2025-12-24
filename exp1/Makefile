# Makefile for Linux System Info Menu
# 项目名称: 命令行交互菜单程序
# 编译器: gcc
# 调试器: gdb

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS = 

# 目录设置
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# 目标文件名
TARGET = $(BIN_DIR)/sysinfo

# 源文件
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/menu.c \
          $(SRC_DIR)/logger.c \
          $(SRC_DIR)/cpu_info.c \
          $(SRC_DIR)/process_info.c \
          $(SRC_DIR)/memory_info.c \
          $(SRC_DIR)/storage_info.c

# 目标文件
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/menu.o \
          $(OBJ_DIR)/logger.o \
          $(OBJ_DIR)/cpu_info.o \
          $(OBJ_DIR)/process_info.o \
          $(OBJ_DIR)/memory_info.o \
          $(OBJ_DIR)/storage_info.o

# 头文件
HEADERS = $(INC_DIR)/menu.h \
          $(INC_DIR)/logger.h \
          $(INC_DIR)/cpu_info.h \
          $(INC_DIR)/process_info.h \
          $(INC_DIR)/memory_info.h \
          $(INC_DIR)/storage_info.h

# 默认目标
all: dirs $(TARGET)

# 创建目录
dirs:
	@mkdir -p $(OBJ_DIR)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "编译完成: $(TARGET)"

# 编译规则
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/menu.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.c $(INC_DIR)/menu.h $(INC_DIR)/cpu_info.h \
                   $(INC_DIR)/process_info.h $(INC_DIR)/memory_info.h \
                   $(INC_DIR)/storage_info.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/logger.o: $(SRC_DIR)/logger.c $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/cpu_info.o: $(SRC_DIR)/cpu_info.c $(INC_DIR)/cpu_info.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/process_info.o: $(SRC_DIR)/process_info.c $(INC_DIR)/process_info.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/memory_info.o: $(SRC_DIR)/memory_info.c $(INC_DIR)/memory_info.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/storage_info.o: $(SRC_DIR)/storage_info.c $(INC_DIR)/storage_info.h $(INC_DIR)/logger.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件
clean:
	rm -rf $(OBJ_DIR) $(TARGET) log.txt
	@echo "清理完成"

# 重新编译
rebuild: clean all

# 调试运行
debug: $(TARGET)
	gdb $(TARGET)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 显示帮助
help:
	@echo "可用目标:"
	@echo "  all     - 编译项目 (默认)"
	@echo "  clean   - 清理编译文件"
	@echo "  rebuild - 重新编译"
	@echo "  debug   - 使用gdb调试"
	@echo "  run     - 运行程序"
	@echo "  help    - 显示此帮助信息"

.PHONY: all dirs clean rebuild debug run help
