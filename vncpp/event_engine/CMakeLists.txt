cmake_minimum_required(VERSION 3.10)

project(event_engine)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(event_engine EventEngine.cpp)