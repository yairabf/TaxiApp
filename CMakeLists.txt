cmake_minimum_required(VERSION 3.5.1)
project(adprog1_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES main.cpp src/Point.cpp src/Point.h src/Node.h src/NodeBlock.cpp src/NodeBlock.h
        src/Map.cpp src/Map.h src/BreadthFirstSearch.cpp
        src/BreadthFirstSearch.h test/PointTest.cpp src/Taxi.cpp src/Taxi.h
        test/TaxiTest.cpp src/TripInfo.h src/TripInfo.cpp
        test/NodeBlockTest.cpp test/MapTest.cpp test/BreadthFirstSearchTest.cpp
        src/Driver.cpp src/Driver.h test/DriverTest.cpp src/Passenger.cpp
        src/Passenger.h test/PassengerTest.cpp src/TaxiStation.cpp src/TaxiStation.h
        test/TaxiStationTest.cpp src/MainFlow.cpp src/MainFlow.h src/ClientDriver.cpp src/ClientDriver.h src/Server.cpp src/Server.h)
add_executable(adprog1_1 ${SOURCE_FILES})
target_link_libraries(adprog1_1)
