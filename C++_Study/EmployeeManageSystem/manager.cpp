//
// Created by GOD婴宁 on 2024/4/12.
//

#include "manager.h"

manager::manager(int id, string name, int dId) {
    this->id = id;
    this->name = name;
    this->deptId = dId;
}

void manager::showMessage() {
    cout << "职工编号:" << this->id
         << "\t姓名:" << this->name
         << "\t岗位:" << this->getDeptName()
         << "\t岗位职责:完成老板交给的任务,并下发任务给员工" << endl;
}

string manager::getDeptName() {
    return string("经理");
}