cmake_minimum_required(VERSION 3.10)

project(vn-cpp)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

if (UNIX)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
    endif ()

    set(CXX_FLAGS
            -g
            -fPIC
            -Wall
            -D__STDC_FORMAT_MACROS
            -Wno-unused-parameter
            -Wno-unused-function
            -Wunused-variable
            -Wunused-value
            -Wshadow
            -Wcast-qual
            -Wcast-align
            -Wwrite-strings
            -Wsign-compare
            -Winvalid-pch
            -fms-extensions
            -Wfloat-equal
            -Wextra
            -std=c++11
            )

    include_directories(${PROJECT_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/3rdparty)
endif (UNIX)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(vncpp)
add_subdirectory(test)

add_executable(${PROJECT_NAME} vncpp/main.cc)
