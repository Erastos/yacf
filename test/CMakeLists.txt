cmake_minimum_required(VERSION 3.10)

project(YACFTest VERSION 0.0.1)
set(CMAKE_BUILD_TYPE Debug)

link_directories("../build/")

add_executable(YACFTest main.cpp)

target_link_libraries(YACFTest YACF)
