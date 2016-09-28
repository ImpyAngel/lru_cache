cmake_minimum_required(VERSION 3.5)
project(lru_cache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lru_cache.cpp lru_cache.h)
add_executable(lru_cache ${SOURCE_FILES})