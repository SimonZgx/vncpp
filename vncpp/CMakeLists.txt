cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(event_engine)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME} event_engine)