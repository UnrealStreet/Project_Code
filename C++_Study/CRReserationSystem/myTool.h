//
// Created by GOD婴宁 on 2024/4/23.
//
#pragma once

#include <iostream>
#include <cmath>
#include <utility>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <map>
#include <string>

using namespace std;
//管理员文件
#define ADMIN_FILE "F:\\Project_Code\\C++_Study\\CRReserationSystem\\admin.txt"
//学生文件
#define STUDENT_FILE "F:\\Project_Code\\C++_Study\\CRReserationSystem\\student.txt"
//老师文件
#define TEACHER_FILE "F:\\Project_Code\\C++_Study\\CRReserationSystem\\teacher.txt"
//机房信息文件
#define COMPUTER_FILE "F:\\Project_Code\\C++_Study\\CRReserationSystem\\computerRoom.txt"
//订单文件
#define ORDER_FILE "F:\\Project_Code\\C++_Study\\CRReserationSystem\\order.txt"

int readMenuSelection(int choice);

//int readMenuSelection(int choice,int);

void exitSystem();

void waitConfirm();

void waitConfirm(int input);

char readQuitConfirm();

pair<int, string> selectTime();

string getTime(const string &s, int target_num);