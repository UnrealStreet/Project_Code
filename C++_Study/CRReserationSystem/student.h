//
// Created by GOD婴宁 on 2024/4/22.
//
#pragma once

#include "Identity.h"
#include "ComputerRoom.h"
#include "orderFile.h"

class Student : public Identity {
public:
    int stuId;//学生编号
    vector<ComputerRoom> vCom; //机房容器

    //默认构造函数
    Student();

    //有参构造函数
    Student(int stuId, string name, string pwd);

    //初始化机房信息
    void initComputer();

    //菜单界面
    void operMenu() override;

    //菜单操作总函数
    void menu(Identity *student) override;

    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder() const;

    //取消预约
    void cancelOrder();

    //更新机房信息
    void updateComputerNum();
};

