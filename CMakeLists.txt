cmake_minimum_required(VERSION 3.10)

project(vncpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(vncpp)
add_subdirectory(test)

add_executable(${PROJECT_NAME} vncpp/main.cc)
