cmake_minimum_required(VERSION 3.17)

set(PROJECT_SOURCE_DIR main.cc)

file(GLOB_RECURSE PROJECT_SOURCE *.cc)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

target_link_libraries(${PROJECT_NAME} httplib)