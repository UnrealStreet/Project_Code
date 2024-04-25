//
// Created by GOD婴宁 on 2024/3/1.
//
#include <iostream>

using namespace std;

bool isPrime(int number) {
    cout << "请输入一个数字：";
    cin >> number;
    for (int i = 2; i < number / 2; ++i) {
        if (number % i == 0) {

            return false;
        }
    }
    return true;
}

int main() {
    if (isPrime(9797))
        cout <<"该数是质数!!!";
    else
        cout << "该数不是质数!!!";
    cin.get();
    cin.get();
}