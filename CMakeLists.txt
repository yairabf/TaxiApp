cmake_minimum_required(VERSION 3.6)
project(adprog1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.cpp Point.h Node.h NodeBlock.cpp NodeBlock.h Map.cpp Map.h BreadthFirstSearch.cpp BreadthFirstSearch.h Graph.h)
add_executable(adprog1_1 ${SOURCE_FILES})