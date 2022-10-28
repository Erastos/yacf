cmake_minimum_required(VERSION 3.10)

project(YACF VERSION 0.0.1)
set(CMAKE_BUILD_TYPE Debug)

add_executable(YACFTest main.cpp process.cpp)
add_library(YACF SHARED
            process.cpp)

set_target_properties(YACF PROPERTIES VERSION ${PROJECT_VERSION})
