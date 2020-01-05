cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

aux_source_directory(. DIR_SRCS)
link_libraries(curl)
include_directories(src/include)
include_directories(${DIR_SRCS})

add_executable(main src/main.cpp src/include/Test.cpp src/include/Test.h src/trader/BaseGateway.cpp)