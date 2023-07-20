cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(../timer timer_src)

add_library(
    timer_lib
    SHARED
    ${timer_src}
)

find_package(fmt REQUIRED)

include_directories(${fmt_INCLUDE_DIRS})

target_link_libraries(
    timer_lib
    fmt::fmt
)