cmake_minimum_required(VERSION 3.2)

project(test_boost)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
#    message(${Boost_LIBRARY_DIRS})
#    message(${Boost_LIBRARIES})
endif ()

find_library(pthread REQUIRED)

add_executable(test_boost main.cpp)

target_link_libraries(test_boost ${Boost_LIBRARIES})

target_link_libraries(test_boost pthread)