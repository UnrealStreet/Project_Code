//
// Created by GOD婴宁 on 2024/4/22.
//
#pragma once

#include <algorithm>
#include "student.h"
#include "teacher.h"
#include "ComputerRoom.h"

class Manager : public Identity {
public:
    int managerId;//管理员编号
    vector<Student> vStu;//学生容器
    vector<Teacher> vTea;//教师容器
    vector<ComputerRoom> vCom;//机房容器
    //默认构造函数
    Manager();

    //有参构造函数
    Manager(string name, string pwd);

    //菜单界面函数
    void operMenu() override;

    //菜单操作总函数
    void menu(Identity *manager) override;

    //添加账号
    void addAccount();

    //查看账号
    void showAccount();
    void printAccount(int select);
    //删除账号
    void deleteAccount();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanOrder();

    //初始化容器
    void initVector();

    //初始化机房信息
    void initComputer();

    //检测是否重复 参数1：id 参数2：类型 1表示学生 2表示老师
    bool checkRepeat(int id, int type);

};

