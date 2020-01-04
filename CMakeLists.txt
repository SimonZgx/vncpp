cmake_minimum_required(VERSION 2.8)

project(main)

aux_source_directory(src DIR_SRCS)
add_executable(vncpp DIR_SRCS)

add_executable(main src/main.cpp src/enum.h)