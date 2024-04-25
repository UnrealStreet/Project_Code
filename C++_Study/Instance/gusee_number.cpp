//
// Created by GOD婴宁 on 2024/3/1.
//
#include <iostream>
#include <time.h>

using namespace std;

int main() {
    cout << "------------猜数字游戏------------" << endl;
    //生成一个随机数
    srand(time(0));
    int target = rand() % 100;
    cout << "本次的数字为：" << target << endl;
    cout << "请输入1-100的数字：";
    int num = 0;

    //设置次数
    int chance = 0;
    while (chance < 5) {
        cin >> num;
        if (num == target) {
            cout << "that's right" << endl;
            break;
        } else if (num > target) {
            cout << "猜大了，请再试一次" << endl;
        } else {
            cout << "猜小了，请再试一次" << endl;
        }
        chance++;
    }
    if (chance == 5) {
        cout << "很遗憾，您的机会用完了" << endl;

    }
    return 0;
}