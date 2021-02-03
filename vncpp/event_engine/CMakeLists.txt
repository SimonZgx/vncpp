cmake_minimum_required(VERSION 3.10)

project(event_engine)

find_package(Boost REQUIRED)
list(APPEND ${PROJECT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_library(${PROJECT_NAME} event_engine.cc)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARY_DIRS})