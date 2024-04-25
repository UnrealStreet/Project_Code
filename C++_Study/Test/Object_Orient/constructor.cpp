//
// Created by GOD婴宁 on 2024/4/9.
//
#include <iostream>
#include <vector>
#include "L_common.h"

using namespace std;

class Person {
public:
//    Person() {
//        cout << "无参构造函数!" << endl;
//        mAge = 0;
//    }
    Person() {
        cout << "无参构造函数!" << endl;
    }

    Person(int age) : age(age) {
        cout << "有参构造函数!" << endl;
//        mAge = age;
    }

//    Person(const Person& p) {
//        cout << "拷贝构造函数!" << endl;
//        mAge = p.mAge;
//    }
    //析构函数在释放内存之前调用
    ~Person() {
        cout << "析构函数!" << endl;
    }

public:
    int age;
};

/*Person doWork() {
    Person p1= {};
    cout << (int *)&p1 << endl;
    return p1;
}
Person test01() {
    Person p = doWork();
    cout <<(int *) &p << endl;
    return p;   // 会调用拷贝构造函数
}
Person doWork1(Person p1 ) {
    cout <<"p1的地址："<< &p1 << endl;
    Person p2 = p1;
    cout << "拷贝后P2的地址："<<&p2 << endl;
    return p2;
}*/
int main() {
//    Person a;
//    Person p = doWork1(a);
//    cout << &p << endl;
//    Person p = test01();
//    cout << &p << endl;
//    Person p;
//    Person p1(p);
    cout << 1;
    return 0;
}


