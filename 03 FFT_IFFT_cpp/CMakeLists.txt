#规定cmake的最低版本要求
cmake_minimum_required (VERSION 3.27)

#项目的名称，不一定和你的文件夹名称一样
project(MySwap)

#打断点调试代码必设置，Cmake默认是Release会导致断点失效
set(CMAKE_BUILD_TYPE "Debug") 

#添加头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

#要用的cpp文件有哪些地址就要添加源文件路径
#将源文件列表写在变量SrcFiles中
aux_source_directory(./source SrcFiles)

#工程项目较大，要创建多个模块
aux_source_directory(./include SrcFiles)

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/build)

#设置可执行文件的名称，make之后build目录下出现main.exe
add_executable(main ${SrcFiles})
