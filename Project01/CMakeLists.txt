cmake_minimum_required(VERSION 3.0)

project(MA)


find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})