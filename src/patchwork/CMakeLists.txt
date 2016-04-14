cmake_minimum_required(VERSION 3.4)
project(PatchWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

SET(PATCHWORK_LIB patchwork.h
        patchwork.cpp
        Circle.h
        Circle.cpp
        figure.hpp
        figure.cpp
        Image.h
        Image.cpp
        Line.h
        Line.cpp
        point.hpp
        point.cpp
        Rectangle.h
        Rectangle.cpp Polygon.cpp Polygon.h)

set(INCLUDE_DIR .)

include_directories(${INCLUDE_DIR})

set(SHARED_LIB_INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)

add_library(patchwork STATIC ${PATCHWORK_LIB})