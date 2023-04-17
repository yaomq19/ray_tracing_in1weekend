cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rayTracing)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)
add_library(rayTracingLib STATIC 
./src/transform.cpp
./src/aabb.cpp
./src/axis_aligned_rect.cpp
./src/box.cpp
./src/bvh.cpp
./src/camera.cpp
./src/hitable_list.cpp
./src/material.cpp
./src/movingSphere.cpp
./src/myMath.cpp
./src/perlin.cpp
./src/ray.cpp
./src/renderer.cpp
./src/sphere.cpp
./src/texture.cpp
./src/constant_medium.cpp)


add_executable(rayTracing ./src/finalScene.cpp)
target_include_directories(rayTracingLib
    PRIVATE
    "./include"
)
target_include_directories(rayTracing
    PRIVATE
    "./include"
)
target_link_libraries(rayTracing rayTracingLib)
