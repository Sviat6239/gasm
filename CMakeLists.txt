cmake_minimum_required(VERSION 3.16)
project(gasm)

set(CMAKE_CXX_STANDARD 26)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(gasm main.cpp ${SRC_FILES})
