cmake_minimum_required(VERSION 2.8)
project(vncpp)

add_definitions(-std=c++14)

link_libraries(curl)

add_executable(vncpp main.cpp)