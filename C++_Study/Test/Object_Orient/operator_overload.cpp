//
// Created by GOD婴宁 on 2024/4/7.
//
#include <iostream>

using namespace std;

class myInteger {
    friend ostream &operator<<(ostream &cout, myInteger m_I);

private:
    int m_int;
public:
    myInteger() = default;

    myInteger(int a) : m_int(a) {
    }

    //前置--重载
    myInteger &operator--() {
        this->m_int--;
        return *this;
    }

    //后置--重载
    myInteger operator--(int) {
        myInteger temp;
        temp.m_int = this->m_int;
        this->m_int--;
        return temp;
    }
};

ostream &operator<<(ostream &cout, myInteger m_I) {
    cout << m_I.m_int;
    return cout;
}

int main() {
    myInteger m_I(10);
//    cout << --(--m_I) << endl;
//    int a = 10;
//    cout << (a--)-- << endl;
    cout << m_I.operator--(1) << endl;
    cout << m_I;
    return 0;
}

