//
// Created by GOD婴宁 on 2024/4/22.
//
#pragma once

#include "Identity.h"
#include "myTool.h"
#include "orderFile.h"
#include "ComputerRoom.h"

class Teacher : public Identity {
public:
    int empId;//教师编号
    vector<ComputerRoom> vCom; //机房容器
    //默认构造函数
    Teacher();

    //有参构造函数
    Teacher(int empId, string name, string pwd);

    //初始化机房信息
    void initComputer();

    //菜单界面
    void operMenu() override;

    //菜单操作总函数
    void menu(Identity *teacher) override;

    //审核预约
    void validOrder();

    //更新机房信息
    void updateComputerNum();
};
