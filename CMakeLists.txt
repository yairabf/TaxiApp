cmake_minimum_required(VERSION 3.5.1)
project(adprog1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/ -lboost_serialization" )
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES src/Point.cpp src/Point.h src/Node.h src/NodeBlock.cpp src/NodeBlock.h
        src/Map.cpp src/Map.h src/BreadthFirstSearch.cpp
        src/BreadthFirstSearch.h src/Taxi.cpp src/Taxi.h src/TripInfo.h src/TripInfo.cpp
        src/Driver.cpp src/Driver.h src/Passenger.cpp
        src/Passenger.h src/TaxiStation.cpp src/TaxiStation.h
        src/ClientDriver.cpp src/ClientDriver.h src/Server.cpp src/Server.h src/Udp.cpp src/Udp.h src/Socket.h src/Socket.cpp)

add_executable(server  src/Server.cpp ${SOURCE_FILES})
add_executable(client src/ClientDriver.cpp ${SOURCE_FILES})
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})