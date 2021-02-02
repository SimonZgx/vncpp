cmake_minimum_required(VERSION 3.10)

project(event_engine)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} event_engine.cc)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARY_DIRS})