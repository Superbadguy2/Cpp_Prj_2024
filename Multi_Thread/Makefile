# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -std=c++11 -pthread -Wall

# 定义目标文件名
TARGET = multi_thread

# 定义依赖的库（如果有的话）
LIBS = 

# 定义需要编译的源文件
SOURCES = multi_thread.cpp

# 定义对象文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

# 伪目标，避免与文件名冲突
.PHONY: all clean
