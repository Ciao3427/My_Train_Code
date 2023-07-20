cmake_minimum_required(VERSION 3.10.2)

include_directories(include)

add_library(
    # 创建可共享的动态库(共享动态库) serial_lib
    serial_lib # 生成的库名称
    SHARED # 生成的库的类型
    # include/serial.hpp
    src/serial.cpp # 指定要生成库的文件
)

include_directories(${HEADPATH})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
