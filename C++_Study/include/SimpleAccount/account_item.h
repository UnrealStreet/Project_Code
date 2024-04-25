//
// Created by GOD婴宁 on 2024/3/7.
//
#pragma once//C___STUDY_ACCOUNT_ITEM_H

#include "common.h"

//定义基本项信息
struct AccountItem {
    string itemType;
    int amount;
    string detail;
};

//针对账目数据进行操作的函数声明

//加载账目数据
void loadDataFromFile(vector<AccountItem> &items);

//记账
void Add(vector<AccountItem> &items);
void insertIntoFile(const AccountItem &item);
void income(vector<AccountItem> &items);
void expand(vector<AccountItem> &items);

//查询
void Query(const vector<AccountItem> &items);
void printItem(const AccountItem &item);
void queryItems(const vector<AccountItem> &items);
void queryItems(const vector<AccountItem> &items, const string &type) ;
