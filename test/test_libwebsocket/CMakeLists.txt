cmake_minimum_required(VERSION 3.2)

project(test)

add_definitions(-std=c++14)

find_path(LWS_INCLUDE_DIR libwebsockets.h
        /usr/local/include
        /usr/include)

find_library(LWS_LIBRARIES_DIR websockets
        /usr/local/lib
        /usr/lib)
include_directories(${LWS_INCLUDE_DIR})
include_directories(BEFORE /usr/local/Cellar/openssl/1.0.2t/include)
find_library(OPENSSL_LIB ssl PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)
find_library(CRYPTO_LIB crypto PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)


link_libraries(${LWS_LIBRARIES_DIR})

add_executable(main main.cpp)