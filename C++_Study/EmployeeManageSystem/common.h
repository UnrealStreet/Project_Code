//
// Created by GOD婴宁 on 2024/4/11.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int readMenuSelection(int choice);

enum choice {
    Exit,
    ADD,
    SHOW,
    DELETE,
    MODIFY,
    SEARCH,
    SORT,
    CLEAR
};
enum deptId {
    EMPLOYEE = 1,
    MANAGER,
    BOSS
};

void waitConfirm();