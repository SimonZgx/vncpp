cmake_minimum_required(VERSION 2.8)

project(libevent-test)

set(CMAKE_CXX_STANDARD 14)

set(SRC_DIR main.cpp)

set(INCLUDE_DIR include
        /usr/local/include
        /usr/include)

list(APPEND ${SRC_DIR} test.cpp)

#find_library(libevent /usr/local/lib)

add_executable(test ${SRC_DIR})

target_link_libraries(test event)