cmake_minimum_required(VERSION 3.10.2) #最小版本

project(SE) # 工程名称

# 生成可执行文件，名称为SE
add_executable(${PROJECT_NAME} main.cpp)

# 给当前节点添加子节点
add_subdirectory(my_libs) # 编译根目录CMakeLists.txt的同时编译子文件夹的CMakelist.txt

# target_link_libraries(${PROJCET_NAME} PUBLIC SHARED)
# target_include_directories(${PROJCET_NAME} PUBLIC my_libs/include)
target_link_libraries(${PROJECT_NAME} serial_lib) # 链接可执行文件 SE 和子目录中创建的共享动态库 serial_lib



SET(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# Setting c++ 11 standardd
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置头文件的路径
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

message("the opencv version is " ${OpenCV_VERSION})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})


