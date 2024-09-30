//
// Created by GOD婴宁 on 2024/7/22.
//
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int shared = 0;
mutex mtx;

void func(int n) {
    for (int i = 0; i < n; ++i) {
        mtx.lock();
        shared++;
        mtx.unlock();
    }
}
int main() {
    thread t1(func, 100000);
    thread t2(func, 100000);
    t1.join();
    t2.join();
    cout << shared << endl;
    system("pause");
    return 0;
}