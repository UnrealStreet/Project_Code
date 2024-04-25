//
// Created by GOD婴宁 on 2024/4/22.
//
#pragma once

#include <string>
#include <fstream>
#include "Identity.h"
#include "myTool.h"

using namespace std;

void mainMenu();

//登录功能 参数1：文件名 参数2：身份类型
void loginIn(const string &fileName, int type);

