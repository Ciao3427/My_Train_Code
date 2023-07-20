cmake_minimum_required(VERSION 3.15)

project(CAMERA_CALIBRATION)

add_executable(CAMERA_CALIBRATION main.cpp)
add_executable(TEST test.cpp)

add_subdirectory(my_libs/camera)
add_subdirectory(my_libs/timer)

target_link_libraries(CAMERA_CALIBRATION camera_lib timer_lib)
target_link_libraries(TEST camera_lib timer_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(CAMERA_CALIBRATION ${OpenCV_LIBS})
target_link_libraries(TEST ${OpenCV_LIBS})



find_package(fmt REQUIRED)
include_directories(${fmt_INCLUEDE_DIRS})
target_link_libraries(CAMERA_CALIBRATION ${fmt_LIBS})
target_link_libraries(TEST ${fmt_LIBS})

