cmake_minimum_required(VERSION 3.24)
project(DEMO C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER F:/MinGW/mingw64/bin/gcc.exe)#指定使用的c编译器
set(CMAKE_CXX_COMPILER F:/MinGW/mingw64/bin/g++.exe)#指定使用的c++编译器

#set(CMAKE_C_FLAGS “${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK”)//解决中文乱码的一种方法，貌似不行
include_directories(${PROJECT_SOURCE_DIR}/include)#引入绝对路径include文件下的头文件


add_executable(main main.c)#配置多个main函数运行环境
add_executable(TestFunction Test/TestFunction.c)
add_executable(test1 Backgammon/test.c Backgammon/game.c)

add_executable(BubbleSort Functions/BubbleSort.c)
add_executable(demo demo.c)
add_executable(test AddressBook/test.c AddressBook/AddressBook.c)
add_executable(DataTest DataStructure/DataTest.c DataStructure/String/SString.c DataStructure/List/Linear.c)