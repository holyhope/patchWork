cmake_minimum_required(VERSION 3.4)
project(PatchWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(server ${SOURCE_FILES})

target_link_libraries(server patchwork)