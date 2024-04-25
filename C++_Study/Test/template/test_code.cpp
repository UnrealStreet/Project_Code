//
// Created by GOD婴宁 on 2024/4/13.
//
#include <iostream>

using namespace std;

template<typename T>
void print(T t) {
    cout << "1" << t << endl;
}

void print(int t) {
    cout << "2 " << t << endl;
}

int main() {
    print<>(1);
    system("pause");
    return 0;
}
