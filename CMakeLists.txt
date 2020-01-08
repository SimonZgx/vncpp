cmake_minimum_required(VERSION 2.8)

project(main)

include_directories(include)

add_executable(main src/main.cpp src/trader/BaseGateway.cpp src/trader/http/http.h include/http/connection.h include/RestClient.h src/trader/http/connection.cpp)