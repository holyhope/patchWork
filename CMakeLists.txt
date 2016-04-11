cmake_minimum_required(VERSION 3.4)
project(PatchWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES main.cpp
        src/patchwork/point.cpp
        src/patchwork/point.h
        src/patchwork/figure.hpp
        src/patchwork/Circle.cpp
        src/patchwork/Circle.h
        src/patchwork/Rectangle.cpp
        src/patchwork/Rectangle.h
        src/patchwork/Line.cpp
        src/patchwork/Line.h
        src/patchwork/Image.cpp
        src/patchwork/Image.h
        #src/serverSide.cpp
        #src/clientSide.cpp
        )
add_executable(PatchWork ${SOURCE_FILES})