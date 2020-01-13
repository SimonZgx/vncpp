cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

aux_source_directory(. DIR_SRCS)

include_directories(include)

link_libraries(curl)

find_package(CURL REQUIRED)

target_link_libraries(CURL::libcurl)

add_executable(main src/main.cpp src/trader/http/connection.cpp src/trader/RestClient.cpp)
