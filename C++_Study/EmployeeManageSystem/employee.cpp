//
// Created by GOD婴宁 on 2024/4/11.
//

#include "employee.h"

employee::employee(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptId = dId;
}

void employee::showMessage() {
    cout << "职工编号:" << this->id
         << "\t姓名:" << this->name
         << "\t岗位:" << this->getDeptName()
         << "\t岗位职责:完成经理交给的任务" << endl;
}

string employee::getDeptName() {
    return string("员工");
}


