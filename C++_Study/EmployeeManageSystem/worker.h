//
// Created by GOD婴宁 on 2024/4/11.
//
#pragma once

#include "common.h"

class worker {
public:
    int id;
    string name;
    int deptId;

    virtual void showMessage() = 0;

    virtual string getDeptName() = 0;

    virtual ~worker() = default;
};
