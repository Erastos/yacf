cmake_minimum_required(VERSION 3.12)

project(yacf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python 3.10 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(yprocess process.cpp)
pybind11_add_module(ysocket socket.cpp)

# add_executable(Test main.cpp test.cpp)
