cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rayTracing)
set(CMAKE_CXX_STANDARD 11)
add_executable(rayTracing ./src/bvh.cpp)
target_include_directories(rayTracing
PUBLIC
"./include")