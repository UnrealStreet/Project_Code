//
// Created by GOD婴宁 on 2024/4/11.
//
#pragma once
#include "worker.h"

class employee : public worker {
public:
    employee(int id, string name, int dId);

    void showMessage() override;

    string getDeptName() override;

};
