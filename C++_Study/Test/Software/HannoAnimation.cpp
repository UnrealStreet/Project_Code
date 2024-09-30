//
// Created by GOD婴宁 on 2024/8/14.
//

#include <graphics.h>
#include <conio.h>
#include <vector>
#include<stack>
#include <iostream>
#include <chrono>

using namespace std;
// 获取开始时间点
auto start = std::chrono::high_resolution_clock::now();
// 定义盘子的数量
int N = 3;
int all = 0;

// 定义盘子的宽度和塔座
vector<int> plateSize(N + 1);
RECT towers[3];

//定义每个塔的盘子数量
vector<stack<int>> towerPlants(3);
//定义移动速度
int speeds[3] = {1000,500,100};
int speed = 1000;
// 初始化图形环境
void init() {
    initgraph(640, 480);
    setbkcolor(WHITE);

    cleardevice();
    // 初始化塔座和盘子的位置
    towers[0] = {100, 100, 120, 400};
    towers[1] = {300, 100, 320, 400};
    towers[2] = {500, 100, 520, 400};
    // 设置文字颜色
    settextcolor(RED);

    // 设置文字大小
    settextstyle(30, 0, _T("楷体"));
    // 输出提示信息
    outtextxy(0, 200, _T("请输入需要演示的层数："));

    // 接收用户的输入
    char input[5];
    for (int i = 0; i < 5; i++) {
        input[i] = _getch();
        if (input[i] == '\r') {  // 如果用户按下回车键，结束输入
            input[i] = '\0';
            break;
        } else {
            // 显示用户的输入
            outtextxy(320 + i * 15, 200, input[i]);
        }
    }
    // 将输入的字符转换为整数
    int num = atoi(input);
    // 将接收到的整数赋值给其他变量
    N = num;
    plateSize.resize(N + 1);

    outtextxy(0, 260, _T("请选择演示速度：1.慢 2.中 3.快"));
    char speedInput = _getch();
    string base = "慢中快";
    int index = speedInput - '1';
    speed = speeds[index];
    index = index * 2;
    string str = "您选择的速度为:" + base.substr(index, 2) ;
    cout << base[index] << endl;
    outtextxy(0,300, _T(str.c_str()));
    outtextxy(0, 340, _T("2s后开始进行演示"));
    Sleep(2000);
    cleardevice();
    //画出塔座
    for (auto &tower: towers) {
        setfillcolor(BLUE);
        fillrectangle(tower.left, tower.top, tower.right, tower.bottom);
    }
    //编辑盘子的宽度
    for (int i = 1; i < N + 1; i++) {
        plateSize[i] = 10 * i;
        setfillcolor(RED);
        fillrectangle(100 - plateSize[i] / 2, 400 - 20 * (N - i + 1), 120 + plateSize[i] / 2, 400 - 20 * (N - i));
    }

    //初始化每个塔的盘子信息
    for (int i = N; i >= 1; i--) {
        towerPlants[0].push(i);
    }
    // 设置文字颜色
    settextcolor(BLUE);

    // 设置文字大小
    settextstyle(30, 0, _T("宋体"));

    // 在指定位置输出文字
    for (int i = 0; i < 3; i++) {
        char txt = 'A' + i;
        outtextxy(towers[i].left + 3, towers[i].bottom + 10, _T(txt));
    }
    Sleep(1000);
    start = std::chrono::high_resolution_clock::now();
}

// 定义移动盘子的函数
void move(int a, int b) {
    all++;
    int del = (int)towerPlants[a].size();
    int plate = towerPlants[a].top();
    towerPlants[a].pop();
    int insert = (int)towerPlants[b].size() + 1;
    towerPlants[b].push(plate);
    //移动盘子
    //1.先删除旧盘子
    setfillcolor(WHITE);
    fillrectangle(towers[a].left - plateSize[plate] / 2, towers[a].bottom - 20 * del,
                  towers[a].right + plateSize[plate] / 2, towers[a].bottom - 20 * (del - 1));
    //2.填充柱子的空白部分
    setfillcolor(BLUE);
    fillrectangle(towers[a].left, 100, towers[a].right, towers[a].bottom - 20 * (del - 1));
    //3.画出新的盘子
    setfillcolor(RED);
    fillrectangle(towers[b].left - plateSize[plate] / 2, towers[b].bottom - 20 * insert,
                  towers[b].right + plateSize[plate] / 2, towers[b].bottom - 20 * (insert - 1));

    //移动信息显示
    settextcolor(RED);
    settextstyle(30, 0, _T("楷体"));
    char txt = 'A' + a;
    char txt2 = 'A' + b;
    char str[5] = {txt, '-', '>', txt2, '\0'};
    outtextxy(towers[1].left - 18, towers[1].top - 40, _T(str));
    Sleep(speed);
}

// 定义汉诺塔的移动算法
void hanoi(int n, int a, int b, int c) {
    if (n == 1) {
        move(a, c);
    } else {
        hanoi(n - 1, a, c, b);
        move(a, c);
        hanoi(n - 1, b, a, c);
    }
}


int main() {
    // 初始化图形环境
    init();

    // 执行汉诺塔的移动算法
    hanoi(N, 0, 1, 2);

    // 获取结束时间点
    auto stop = std::chrono::high_resolution_clock::now();

    // 计算持续时间，单位为毫秒
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    int time = (int) duration.count();
    string str = "移动消耗时间为:" + to_string(time) + "毫秒";
    str += " 总共移动" + to_string(all) + "次";
    // 设置文字颜色
    settextcolor(RED);
    // 设置文字大小
    settextstyle(30, 0, _T("楷体"));
    outtextxy(40, 440, _T(str.c_str()));
    // 按任意键退出
    _getch();
    closegraph();
    return 0;
}