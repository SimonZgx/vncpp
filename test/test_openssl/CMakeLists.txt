cmake_minimum_required(VERSION 3.2)

project(test)

add_definitions(-std=c++14)

include_directories(BEFORE /usr/local/Cellar/openssl/1.0.2t/include)
find_library(OPENSSL_LIB ssl PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)
find_library(CRYPTO_LIB crypto PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)

link_libraries(${OPENSSL_LIB})

link_libraries(${CRYPTO_LIB})

add_executable(main main.cpp)