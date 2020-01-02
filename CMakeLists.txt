cmake_minimum_required(VERSION 2.8)

project(main)

include_directories(src/trader)

aux_source_directory(. DIR_SRCS)


add_executable(main src/main.cpp)