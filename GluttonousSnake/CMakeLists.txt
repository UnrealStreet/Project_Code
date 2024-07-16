cmake_minimum_required(VERSION 3.24)
project(GluttonousSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

link_libraries(libeasyx.a)
add_executable(GluttonousSnake main.cpp)
