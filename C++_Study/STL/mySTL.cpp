//
// Created by GOD婴宁 on 2024/4/22.
//
#include <iostream>
#include <string>
#include <random>
#include <chrono>

using namespace std;
//确认输入合法性
int readMenuSelection(int choice) {
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || message[0] - '0' < 0 || message[0] - '0' >= choice)
            cout << "输入错误，请重新输入：";
        else
            break;
    }
    int ans = message[0] - '0';
    //输入正确
    return ans;
}
//暂停窗口等待输入以继续
void waitConfirm() {
    cout << "请按回车键以继续...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string message;
    getline(cin, message); //防止直接退出
}

//随机数生成
int randomNum() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//1.种子:当前时间戳（毫秒）
    mt19937 gen(seed); //2.随机数生成引擎 使用当前时间戳（毫秒）作为种子初始化随机数生成器
    uniform_int_distribution<> dis(600, 1000); //3.随机数分布器 定义浮点数分布范围
    return dis(gen);
}
//绘制系统退出界面(绘制心形图案) (x^2+y^2-0.64)^3-x^2*y^3=0
void exitSystem() {
    //1.设置绘图边界
    double a = 0.64;
    double bound = 1.3 * sqrt(a);
    //2.开始制图
    //x,y 坐标
    double step = 0.05;//步长
    for (double y = bound; y >= -bound; y -= 2 * step) {
        for (double x = -bound; x <= bound; x += step) {
            double result = pow((pow(x, 2) + pow(y, 2) - a), 3) - pow(x, 2) * pow(y, 3);
            if (result <= 0)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}