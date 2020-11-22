cmake_minimum_required(VERSION 3.17)
project(Image_Quad_Tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lX11")
set(CMAKE_CXX_FLAGS "-lpthread")
set(CMAKE_CXX_FLAGS "-ljpeg")

add_executable(Image_Quad_Tree main.cpp)

target_link_libraries(Image_Quad_Tree -lX11 -lpthread -ljpeg)