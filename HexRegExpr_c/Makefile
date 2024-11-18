# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -g  # 启用所有警告，并包含调试信息 (-g)

# 目标可执行文件名
TARGET = hexmatch

# 源文件
SRC = main.c

# 生成目标的目标文件
OBJ = $(SRC:.c=.o)

# 默认目标
all: $(TARGET)

# 编译目标程序
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# 编译源文件为目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件和可执行文件
clean:
	rm -f $(OBJ) $(TARGET)

# 运行程序（用于方便调试）
run: $(TARGET)
	./$(TARGET) 0x1a3f abc 0xABC123  # 示例输入

# 调试目标：带调试信息启动 GDB
debug: $(TARGET)
	gdb ./$(TARGET)  # 启动 GDB 调试器

# 使 make 显示规则中的所有命令
.PHONY: all clean run debug

