cmake_minimum_required(VERSION 2.8)

project(main)

add_definitions(-std=c++14)

set(CMAKE_CXX_FLAGS "-fno-elide-constructors ${CMAKE_CXX_FLAGS}")
add_compile_options(-fno-elide-constructors)

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

link_libraries(curl)

include_directories(/usr/local/opt/openssl/include)

find_package(CURL REQUIRED)
target_link_libraries(CURL::libcurl)

include_directories(BEFORE /usr/local/Cellar/openssl/1.0.2t/include)
find_library(OPENSSL_LIB ssl PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)
find_library(CRYPTO_LIB crypto PATHS /usr/local/Cellar/openssl/1.0.2t/lib NO_DEFAULT_PATH)

link_libraries(${OPENSSL_LIB})

link_libraries(${CRYPTO_LIB})

add_executable(main src/main.cpp src/trader/http/connection.cpp)
