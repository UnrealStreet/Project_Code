//
// Created by GOD婴宁 on 2024/4/12.
//

#pragma once

#include "worker.h"

class manager : public worker {
public:
    manager(int id, string name, int dId);

    void showMessage() override;

    string getDeptName() override;
};
