cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

project(YACF VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(YACF SHARED
            process.cpp)

set_target_properties(YACF PROPERTIES VERSION ${PROJECT_VERSION})

install(TARGETS YACF DESTINATION /usr/lib)
install(FILES include/process.h DESTINATION include)
