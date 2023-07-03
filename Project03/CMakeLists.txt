CMAKE_MINIMUM_REQUIRED(VERSION 3.0)     # 使用最小版本cmake

PROJECT(SWAP)   # 工程名

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # 配置clangd

ADD_EXECUTABLE(SWAP_CMAKE src/main.cpp)     # 添加可执行文件SWAP_CMAKE

INCLUDE_DIRECTORIES(include)    # 包含头文件夹include
