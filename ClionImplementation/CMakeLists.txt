cmake_minimum_required(VERSION 3.29)
project(untitled2)

set(CMAKE_CXX_STANDARD 11)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)
add_executable(untitled2
        main.cpp
        Node.h
        ReadCSV.cpp
        Haversine.cpp
        AStar.cpp
        Dijkstras.h)
find_package(asio CONFIG REQUIRED)
target_link_libraries(untitled2 PRIVATE asio::asio)