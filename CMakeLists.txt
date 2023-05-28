cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(rayTracing)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)
add_library(rayTracingLib STATIC 
./src/acceleration/aabb.cpp
./src/acceleration/axis_aligned_rect.cpp
./src/acceleration/bvh.cpp

./src/hitable/box.cpp
./src/hitable/constant_medium.cpp
./src/hitable/hitable_list.cpp
./src/hitable/movingSphere.cpp
./src/hitable/sphere.cpp
./src/hitable/transform.cpp

./src/material/material.cpp

./src/math/myMath.cpp
./src/math/perlin.cpp

./src/render/camera.cpp
./src/render/ray.cpp
./src/render/renderer.cpp

./src/texture/texture.cpp

./src/tool/parse.cpp
)


add_executable(rayTracing ./src/main.cpp)

# 使用GLOB_RECURSE命令递归地查找include文件夹及其子文件夹中的所有头文件
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

# 使用foreach循环，将每个头文件的路径添加到target_include_directories中
foreach(FILE ${HEADER_FILES})
    get_filename_component(FILE_DIR ${FILE} DIRECTORY) # 获取头文件所在的目录
    target_include_directories(rayTracing PRIVATE ${FILE_DIR}) # 添加头文件所在的目录
    target_include_directories(rayTracingLib PRIVATE ${FILE_DIR}) # 添加头文件所在的目录
endforeach(FILE ${HEADER_FILES})

target_link_libraries(rayTracing rayTracingLib)

