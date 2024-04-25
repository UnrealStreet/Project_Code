cmake_minimum_required(VERSION 3.24)
project(C___Study)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER F:/MinGW/mingw64/bin/gcc.exe)#指定使用的c编译器
set(CMAKE_CXX_COMPILER F:/MinGW/mingw64/bin/g++.exe)#指定使用的c++编译器

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")#该方法使得 relase 模式正常了，但是 debug 反而乱码了
#如果想调试的话删除注释掉即可

include_directories(${PROJECT_SOURCE_DIR}/include/SimpleAccount)#引入绝对路径include文件下的头文件
include_directories(${PROJECT_SOURCE_DIR}/include/Leetcode)#引入绝对路径include文件下的头文件
#include_directories(${PROJECT_SOURCE_DIR}/include/**.h)#引入绝对路径include文件下的头文件

add_executable(main main.cpp)
add_executable(isPrime Instance/isPrime.cpp)
add_executable(gusee_number Instance/gusee_number.cpp)
add_executable(Love_Heart Instance/Love_Heart.cpp)

add_executable(account_main SimpleAccount/account_main.cpp SimpleAccount/operations.cpp SimpleAccount/menus.cpp SimpleAccount/read_cheak.cpp)

add_executable(manage_main EmployeeManageSystem/manage_main.cpp EmployeeManageSystem/workerManager.cpp EmployeeManageSystem/employee.cpp EmployeeManageSystem/manager.cpp EmployeeManageSystem/boss.cpp)

add_executable(system_main SpeechContest/system_main.cpp SpeechContest/speechManager.cpp)
add_executable(CRRS_main CRReserationSystem/CRRS_main.cpp CRReserationSystem/student.cpp  CRReserationSystem/teacher.cpp  CRReserationSystem/manager.cpp CRReserationSystem/globalFile.cpp CRReserationSystem/myTool.cpp CRReserationSystem/orderFile.cpp)