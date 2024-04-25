//
// Created by GOD婴宁 on 2024/4/22.
//
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//定义基类
class Identity {
public:
    virtual void operMenu() = 0;

    virtual void menu(Identity* user) = 0;

    virtual ~Identity() = default;

    std::string m_Name;
    std::string m_Pwd;
};

