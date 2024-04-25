//
// Created by GOD婴宁 on 2024/4/10.
//
#pragma once//防止头文件重复包含

#include "common.h"
#include "worker.h"

#define FILENAME "F:\\Project_Code\\C++_Study\\EmployeeManageSystem\\WorkerFile.csv"

class WorkerManger {
public:
    int workerNum;
    vector<worker *> workerArray;

    WorkerManger();

    ~WorkerManger();

    void show_Menu(); //显示菜单

    void addWorker();//添加职工

    void save(); //保存文件

    void loadFile(); //加载文件

    void showWorker();//显示职工

    void deleteWorker();//删除职工
    int isExist(int id);//判断职工是否存在

    void modifyWorker();//修改职工信息

    void searchWorker();//查找职工

    void sortWorker();//排序职工

    void clearFile();//清空文件
    void exitSystem();
};


