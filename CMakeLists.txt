cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
link_libraries(curl)

find_package(CURL REQUIRED)

target_link_libraries(CURL::libcurl)

#aux_source_directory(src/gateway/bybit/ DIR_SRCS)
#add_executable(main ${DIR_SRCS})
add_executable(main src/main.cpp src/trader/http/connection.cpp src/trader/RestClient.cpp src/gateway/bybit/BybitGateway.cpp include/http/request.h test/test_threadpool/ThreadPool.h test/test_threadpool/main.cpp)
