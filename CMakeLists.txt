cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rayTracing)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)
add_executable(rayTracing ./src/cornellBox.cpp ./src/aabb.cpp ./src/axis_aligned_rect.cpp
)
target_include_directories(rayTracing
PUBLIC
"./include")