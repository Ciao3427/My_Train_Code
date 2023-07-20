cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(../camera camera_src)

add_library(
    camera_lib
    SHARED
    ${camera_src}
)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${fmt_INCLUDE_DIRS})

target_link_libraries(
    camera_lib
    ${OpenCV_LIBS}
    fmt::fmt
    MVSDK
)