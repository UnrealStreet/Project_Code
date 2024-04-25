//
// Created by GOD婴宁 on 2024/4/12.
//

#include "boss.h"

boss::boss(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptId = dId;
}

void boss::showMessage() {
    cout << "职工编号:" << this->id
         << "\t姓名:" << this->name
         << "\t岗位:" << this->getDeptName()
         << "\t岗位职责:管理公司所有事务" << endl;
}

string boss::getDeptName() {
    return string("总裁");
}

