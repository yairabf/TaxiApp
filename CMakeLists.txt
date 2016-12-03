cmake_minimum_required(VERSION 3.6)
project(adprog1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
set(SOURCE_FILES main.cpp Point.cpp Point.h Node.h NodeBlock.cpp NodeBlock.h Map.cpp Map.h BreadthFirstSearch.cpp
        BreadthFirstSearch.h PointTest.cpp TripInfoTest.cpp Taxi.cpp Taxi.h TaxiTest.cpp TripInfo.h TripInfo.cpp
        NodeBlockTest.cpp MapTest.cpp MapTest.h)
add_executable(adprog1_1 ${SOURCE_FILES})
target_link_libraries(adprog1_1 gtest gtest_main)