cmake_minimum_required(VERSION 3.2)

project(test_singleton)

add_definitions(-std=c++14)

add_executable(main main.cpp ThreadPool.h)