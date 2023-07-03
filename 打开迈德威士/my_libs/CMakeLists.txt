cmake_minimum_required(VERSION 3.10)

include_directories(include)

add_library(
    open_lib
    SHARED
    src/mv_camera.cpp
)

include_directories(${HEADPATH})

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(
    open_lib
    ${OpenCV_LIBS}
    fmt::fmt
    MVSDK
)