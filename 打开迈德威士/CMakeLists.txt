cmake_minimum_required(VERSION 3.10)

project(MDWS)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(my_libs)

target_link_libraries(${PROJECT_NAME} open_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

message("The OpenCV version is " ${OpenCV_VERSION})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})