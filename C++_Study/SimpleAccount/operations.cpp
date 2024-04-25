//
// Created by GOD婴宁 on 2024/3/7.
//
#include "common.h"
#include "account_item.h"

//读取文件中的账目数据
void loadDataFromFile(vector<AccountItem> &items) {
    ifstream input(FILENAME);
    //逐行读取每一条数目，包装成AccountItem
    AccountItem item;
    while (input >> item.itemType >> item.amount >> item.detail) {
        items.push_back(item);
    }
    input.close();
}

//记账操作
void Add(vector<AccountItem> &items) {
    int options = 3;
    //读取键盘选择并做合法性校验
    char key = readMenuSelection(options);
    switch (key) {
        case '1'://1-收入
            income(items);
            break;
        case '2'://2-支出
            expand(items);
            break;
        default://3-返回主菜单
            break;
    }
}

//-------------------1.记账-------------------
//记录收入
void income(vector<AccountItem> &items) {
    //新创建一个AccountItem对象
    AccountItem item;
    //确定类型为收入
    item.itemType = INCOME;
    //与用户交互，确认信息
    cout << "\n本次收入金额：";
    item.amount = readAmount();
    cout << "\n备注：";
    getline(cin, item.detail);
    //添加到容器中
    items.push_back(item);
    //写入文件
    insertIntoFile(item);
    cout << "\n---------------记账成功---------------" << endl;
    cout << "请按回车键返回账单....." << endl;
    string line;
    getline(cin, line);
}

//写入文件
void insertIntoFile(const AccountItem &item) {
    //创建一个ofstream对象,以追加方式进行写入
    ofstream output(FILENAME, ios::out | ios::app);
    output << item.itemType << '\t' << item.amount << '\t' << item.detail << endl;
    output.close();
}

//记录支出
void expand(vector<AccountItem> &items) {
//新创建一个AccountItem对象
    AccountItem item;
    //确定类型为支出
    item.itemType = EXPAND;
    //与用户交互，确认信息
    cout << "\n本次支出金额：";
    item.amount = -readAmount();
    cout << "\n备注：";
    getline(cin, item.detail);
    //添加到容器中
    items.push_back(item);
    //写入文件
    insertIntoFile(item);
    cout << "\n---------------记账成功---------------\n" << endl;
    cout << "请按回车键返回账单....." << endl;
    string line;
    getline(cin, line);
}

//-------------------2.查询-------------------
//查询操作
void Query(const vector<AccountItem> &items) {
    int options = 4;
    //读取键盘选择并做合法性校验
    char key = readMenuSelection(options);
    switch (key) {
        case '1'://1-查询所有账目，并统计总收支
            queryItems(items);
            break;
        case '2'://2-查询收入，统计总收入
            queryItems(items, INCOME);
            break;
        case '3'://3-查询支出，统计总支出
            queryItems(items, EXPAND);
            break;
        default:
            break;
    }
}

//查询账目功能函数
//打印一条账目信息
void printItem(const AccountItem &item) {
    cout << item.itemType << "\t\t" << item.amount << "\t\t" << item.detail << endl;
}

void queryItems(const vector<AccountItem> &items) {
    cout << "--------------查询结果--------------" << endl;
    cout << "\n类型\t\t金额\t\t备注\n" << endl;
    //遍历所有账目，统计总收支
    int total = 0;
    for (auto &item: items) {
        printItem(item);
        total += item.amount;
    }
    //输出信息
    cout << "=========================================\n" << endl;
    cout << "总收支：" << total << endl;
    cout << "请按回车键返回账单....." << endl;
    string line;
    getline(cin, line);
}

void queryItems(const vector<AccountItem> &items, const string &type) {
    cout << "--------------查询结果--------------" << endl;
    cout << "\n类型\t\t金额\t\t备注\n" << endl;
    //遍历所有账目，统计总收支
    int total = 0;
    for (auto  &item: items) {
        if (item.itemType != type)
            continue;
        printItem(item);
        total += item.amount;
    }
    //输出信息
    cout << "=========================================\n" << endl;
    cout << (type == INCOME ? "总收入：" : "总支出：") << total << endl;
    cout << "请按回车键返回账单....." << endl;
    string line;
    getline(cin, line);
}

















