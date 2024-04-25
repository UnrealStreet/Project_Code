//
// Created by GOD婴宁 on 2024/3/1.
//
#include <iostream>
#include <cmath>
using namespace std;
//绘制一个爱心
//曲线方程:(x^2+y^2-a)^3-x^2*y^3 = 0
int main() {
    //1.设置绘图边界
    double a = 0.64;
    double bound = 1.3 * sqrt(a);
    //2.开始制图
    //x,y 坐标
    double step = 0.05;//步长
    for (double y = bound; y >= -bound; y -= 2*step) {
        for (double x = -bound; x <= bound; x += step) {
            double result = pow((pow(x, 2) + pow(y, 2) - a), 3) - pow(x, 2) * pow(y, 3);
            if (result <= 0)
                cout << "*";
            else
                cout << " ";
        }
    cout << endl;
    }
    cin.get();
}
