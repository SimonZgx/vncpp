cmake_minimum_required(VERSION 3.10)

project(vn-pp)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vnpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/lib)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)

set(HTTPLIB_REQUIRE_OPENSSL ON)
set(HTTPLIB_REQUIRE_ZLIB ON)

add_compile_definitions(${PROJECT_NAME}
        HTTPLIB_REQUIRE_OPENSSL)

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
            -std=c++14
            )

    include_directories(${PROJECT_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/3rdparty)
endif ()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif ()

add_compile_definitions(${PROJECT_NAME})

add_subdirectory(vnpp)
add_subdirectory(test)
add_subdirectory(3rdparty/cpp-httplib)

