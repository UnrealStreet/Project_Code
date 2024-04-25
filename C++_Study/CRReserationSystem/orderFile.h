//
// Created by GOD婴宁 on 2024/4/23.
//
#pragma once

#include <fstream>
#include "myTool.h"


class OrderFile {
public:
    //构造函数
    OrderFile();

    //更新预约记录
    void updateOrder();

    //截取记录
    static pair<string, string> interOrderData(string& s);

    //查看所有预约
    static void showAllOrder();

    //记录所有预约信息
    map<int, map<string, string>> m_orderData;

    //预约记录条数
    int m_Size;
};