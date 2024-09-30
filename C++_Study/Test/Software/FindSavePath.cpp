//
// Created by GOD婴宁 on2024/8/19.
//
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <ctime>

using namespace std;
const int Height = 720;
const int Width = 960;
const int x = 42;
const int y = 41;
const int square = 15;
int baseL = (Width - x *square) /2, baseT = (Height - y *square) / 2;
int path[x][y];

void init() {
    initgraph(Width, Height);
    setbkcolor(WHITE);
    cleardevice();
    memset(path, 0, sizeof(path));
}

//绘制基础网格
void drawGrid() {
    //绘制2-21行
    for (int i = 1; i < x - 1; i++) {
        for (int j = 0; j < y; j++) {
            if (path[i][j] == 0) {
                setfillcolor(BLACK);
                fillrectangle(baseL + j *square, baseT + i *square, baseL + j *square +square, baseT + i *square +square);
            }
        }
    }
    //绘制第一行和最后一行
    setfillcolor(RGB(128, 0, 128));
    for (int i = 0; i < y; i++) {
        fillrectangle(baseL + i *square, baseT, baseL + i *square +square, baseT +square);
        fillrectangle(baseL + i *square, baseT + (x - 1) *square, baseL + i *square +square, baseT + (x - 1) *square +square);
    }
}

void buriedMine() {
    //随机设置障碍物
    srand(time(0));
    int seedNums = x - 2;
    vector<int> v(seedNums + 1);
    for (int i = 0; i < seedNums + 1; i++)
        v[i] = i;
    for (int i = 1; i < (int) v.size(); i++) {
        int index = rand() % (seedNums + 1);//选取0square之间的随机数
        path[i][v[index]] = 1;//选取的随机数对应的列设置为1
        swap(v[index], v[seedNums]);//将选取的随机数与最后一个元素交换
        seedNums--;//缩小随机数范围
    }
//    绘制障碍物
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (path[i][j] == 1) {
                setfillcolor(RED);
                fillrectangle(baseL + j *square, baseT + i *square, baseL + j *square +square, baseT + i *square +square);
            }
        }
    }
}

//找出安全路径
void findSafePath(vector<vector<int>> &safePath) {
    //第一步：找出第一行的障碍物
    int index = 0;
    for (int i = 0; i < y; i++) {
        if (path[1][i] == 0) {
//            safePath.push_back({1, i});
        } else {
            index = i;
            break;
        }
    }
    //第二步：
    // 1.障碍物在最左边或者最右边
    if (index == 0) {//障碍物在最左边
        safePath.push_back({0, 1});
        index = 2;
        bool isFirst = false;
        for (int i = 1; i < x - 1; i++) {
            index--;
            if (path[i][index] == 0) {
                safePath.push_back({i, index++});
            } else {// get the mine
                isFirst = true;
                break;
            }
            if (path[i][index] == 0)
                safePath.push_back({i, index++});
            else
                break;
        }
        if (isFirst) {
            //delete the last element
            safePath.pop_back();
            int line = safePath.back()[0] + 1;
            for (int i = index - 1; i > 0; i--)
                safePath.push_back({line, i});
            for (int i = line; i < x; i++)
                safePath.push_back({i, 0});
        } else {
            cout << "index: " << index << endl;
            if (index == y + 1) {
                safePath.pop_back();
                safePath.push_back({x - 1, y - 1});
            } else {
                int line = safePath.back()[0];
                for (int i = index - 2; i > 0; i--)
                    safePath.push_back({line, i});
                for (int i = line; i < x; i++)
                    safePath.push_back({i, 0});
            }
        }
        return;
    }
    if (index == y - 1) {//障碍物在最右边
        safePath.clear();
        safePath.push_back({0, y - 2});
        index = y - 3;
        bool isFirst = false;
        for (int i = 1; i < x - 1; i++) {
            index++;
            if (path[i][index] == 0) {
                safePath.push_back({i, index--});
            } else {// get the mine
                isFirst = true;
                break;
            }
            if (path[i][index] == 0)
                safePath.push_back({i, index--});
            else
                break;
        }
        if (isFirst) {
            //delete the last element
            safePath.pop_back();
            int line = safePath.back()[0] + 1;
            for (int i = index + 1; i < y - 1; i++)
                safePath.push_back({line, i});
            for (int i = line; i < x; i++)
                safePath.push_back({i, y - 1});
        } else {
            if (index == -2) {
                safePath.pop_back();
                safePath.push_back({x - 1, 0});
            } else {
                int line = safePath.back()[0];
                for (int i = index + 2; i < y - 1; i++)
                    safePath.push_back({line, i});
                for (int i = line; i < x; i++)
                    safePath.push_back({i, y - 1});
            }
        }
        return;
    }
    // 2.障碍物在中间
    if (path[2][index - 1] == 0) {
//        safePath.clear();
        safePath.push_back({0, index - 1});
        safePath.push_back({1, index - 1});
        safePath.push_back({2, index - 1});
        for (int i = 2; i < x; i++)
            safePath.push_back({i, index});
    } else {
//        safePath.clear();
        safePath.push_back({0, index + 1});
        safePath.push_back({1, index + 1});
        safePath.push_back({2, index + 1});
        for (int i = 2; i < x; i++)
            safePath.push_back({i, index});
    }
}

//绘制安全路径
void drawSafePath(vector<vector<int>> &safePath) {
    for (auto &v: safePath) {
        setfillcolor(GREEN);
        fillrectangle(baseL + v[1] *square, baseT + v[0] *square, baseL + v[1] *square +square, baseT + v[0] *square +square);
        Sleep(100);
    }
}

int main() {
    //初始化图形环境
    init();
    //绘制基础网格
    drawGrid();
    //设置障碍物
    buriedMine();
    //找出安全路径
    vector<vector<int>> safePath;
    findSafePath(safePath);
    //绘制安全路径
    drawSafePath(safePath);
    _getch();
    closegraph();
    return 0;
}