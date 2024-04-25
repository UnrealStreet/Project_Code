//
// Created by GOD婴宁 on 2024/3/7.
//
#include "common.h"

//读取键盘输入的菜单选项，进行合法性校验
char readMenuSelection(int options) {
    string message;
    //进行合法性校验
    while (true) {
    getline(cin, message);
        if (message.size() != 1 || message[0] - '0' <= 0 || message[0] - '0' > options)
            cout << "输入错误，请重新输入：";
        else
            break;
    }
    //输入正确
    return message[0];
}

//读取是否确认的信息，并做合法性校验
char readQuitConfirm() {
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || (toupper(message[0]) != 'Y' && toupper(message[0]) != 'N'))
            cout << "输入错误，请重新输入（Y/N）：";
        else
            break;
    }
    //输入正确
    return toupper(message[0]);
}
//读取键盘输入的金额，并作合法性校验
int readAmount() {
    int amount;
    string money;
    //进行合法性校验
    while (true) {
        getline(cin, money);
        //进行异常检查
        try {
            amount = stoi(money);
            break;
        } catch (invalid_argument& e) {
            cout << "输入错误，请正确输入数字:";
        }
    }
    //输入正确
    return amount;
}









