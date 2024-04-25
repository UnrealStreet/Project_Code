//
// Created by GOD婴宁 on 2024/3/6.
//
#include "common.h"
#include "account_item.h"

int main() {
    //1.加载文件中的账目数据
    vector<AccountItem> items;
    loadDataFromFile(items);

    bool  quit = false;
    int options = 3;
    do {
        //2.显示主菜单
        showMainMenu();
        //3.读取键盘选择并做合法性校验
        char key = readMenuSelection(options);

        switch (key) {
            case '1'://1-记账
                showAddMenu();
                Add(items);
                break;
            case '2'://2-查询
                showQueryMenu();
                Query(items);
                break;
            case '3'://3-退出
                cout << "是否确认退出（Y/N）";
                if (readQuitConfirm() == 'Y')
                    quit = true;
                break;
            default:
                break;
        }
        cout << endl;
    } while (!quit);
}
