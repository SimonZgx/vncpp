cmake_minimum_required(VERSION 3.2)

project(test_boost)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
#    message(${Boost_LIBRARY_DIRS})
#    message(${Boost_LIBRARIES})
endif ()


add_executable(test_boost main.cpp)