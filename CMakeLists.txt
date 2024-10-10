cmake_minimum_required(VERSION 3.10)  # 设置最低 CMake 版本要求
project(test_compiler)                    # 定义项目名称

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)


# 添加源文件并生成可执行文件
add_executable(scanner main.c syntax.tab.c)

target_link_libraries(scanner fl)
