//
// Created by GOD婴宁 on 2024/3/6.
//
#pragma once//C___STUDY_COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define FILENAME "F:\\Project_Code\\C++_Study\\SimpleAccount\\AccountBook.txt"
#define INCOME "收入"
#define EXPAND "支出"

using namespace std;

//通用性功能函数声明

//绘制菜单的函数
void showMainMenu();
void showAddMenu();
void showQueryMenu();
//void showQueryMenu();

//读取键盘输入进行合法性校验的函数
char readMenuSelection(int choice);
char readQuitConfirm();
int readAmount();
