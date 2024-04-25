#include <iostream>
#include <string>
//#include <vector>
//#include <random>
//#include <chrono>
//#include <ctime>
//#include <iomanip>
//#include <algorithm>
//#include <map>

using namespace std;

//class animal {
//public:
//
//    int test;
//
//    virtual void show() = 0;
//};
//
//class dog : public animal {
//public:
//    void show() override {
//        cout << "I'm a dog" << endl;
//    }
//};
//
//class Husky : public dog {
//public:
//    int age;
//    char name[18];
//
//    Husky(int a, char *b, int c) {
//        test = a;
//    }
//
//    void show() override {
//        cout << "I'm a Husky" << endl;
//    }
//};
//
//void work(animal &a) {
//    a.show();
//}


int main(int argc,char *argv[]){
    cout << "argc: " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }
    return 0;
}