cmake_minimum_required(VERSION 3.4)
project(PatchWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES main.cpp
        client.cpp
        client.h)

add_executable(client ${SOURCE_FILES})

target_link_libraries(client patchwork)