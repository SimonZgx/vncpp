cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

aux_source_directory(src DIR_SRCS)
link_libraries(curl)
include_directories(src/include)

add_executable(main src/main.cpp src/include/enum.h test/test_libcurl/main.cpp src/gateway/bybit/rest/BybitRestClient.cpp src/include/BybitRestClient.h src/trader/RestClient.cpp src/include/RestClient.h src/trader/Request.cpp src/include/Request.h)