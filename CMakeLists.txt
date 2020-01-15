cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

aux_source_directory(. DIR_SRCS)

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
link_libraries(curl)

find_package(CURL REQUIRED)

target_link_libraries(CURL::libcurl)

add_executable(main src/main.cpp src/trader/http/connection.cpp src/trader/RestClient.cpp)
