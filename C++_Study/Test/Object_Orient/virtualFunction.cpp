//
// Created by GOD婴宁 on 2024/4/8.
//
#include <iostream>
using namespace std;

class animal{
public:
    virtual void speak(){
        cout << "动物在说话" << endl;
    }
};
class cat:public animal{
public:
     void speak() override{
        cout <<"猫猫在说话"<<endl;
    }
};
int main(){
    int size = sizeof (cat);
    cout << size <<endl;
    cat a;
    animal & b = a;
    b.speak();
    return 0;
}