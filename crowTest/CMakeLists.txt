cmake_minimum_required(VERSION 3.29)
project(crow)

set(CMAKE_CXX_STANDARD 11)
add_executable(crow main.cpp
        crow_all.h)
find_package(asio CONFIG REQUIRED)
target_link_libraries(crow PRIVATE asio::asio)


