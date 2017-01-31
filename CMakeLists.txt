cmake_minimum_required(VERSION 3.5.1)
project(adprog1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/ -lboost_serialization" )
set(BOOST_ROOT CACHE PATH "/usr/include/boost/ -lboost_log" )
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES src/Point.cpp src/Point.h src/Node.h src/NodeBlock.cpp src/NodeBlock.h
        src/Map.cpp src/Map.h src/BreadthFirstSearch.cpp
        src/BreadthFirstSearch.h src/Taxi.cpp src/Taxi.h src/TripInfo.h src/TripInfo.cpp
        src/Driver.cpp src/Driver.h src/Passenger.cpp
        src/Passenger.h src/TaxiStation.cpp src/TaxiStation.h
        src/Udp.cpp src/Udp.h src/Socket.h src/Socket.cpp src/Tcp.cpp src/Tcp.h
        src/InfoForTripThread.cpp src/InfoForTripThread.h easylogging++.h src/InputValidityTests.cpp
        src/InputValidityTests.h)

add_executable(server src/Server.cpp src/Server.h ${SOURCE_FILES})
add_executable(client src/Client.cpp src/Client.h ${SOURCE_FILES} src/InputValidityTests.cpp
        src/InputValidityTests.h)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})