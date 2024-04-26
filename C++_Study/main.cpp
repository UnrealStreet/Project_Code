#include <iostream>
#include <string>
//#include <vector>
//#include <random>
//#include <chrono>
//#include <ctime>
//#include <iomanip>
//#include <algorithm>
#include <map>

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


//int main(int argc,char *argv[]){
//    cout << "argc: " << argc << endl;
//    for (int i = 0; i < argc; ++i) {
//        cout << "argv[" << i << "]: " << argv[i] << endl;
//    }
//    return 0;
//}


//int main() {
//    // 获取当前时间
//    auto now = std::chrono::system_clock::now();
//
//    // 将时间点转换为时间_t
//    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
//
//    // 将时间_t转换为日期字符串
//    std::tm tm{};
//    localtime_s(&tm, &now_time_t);
//    int month = tm.tm_mon + 1;
//    int day = tm.tm_mday;
//    // 按照 "月日" 的格式打印日期
//    std::cout << std::put_time(&tm, "%m月%d日") << std::endl;
//    string s = "04月30日(周五)";
//    s = s.substr(4, 2);
//    cout << stoi(s) << endl;
//    cout << month << " " << day << endl;
//    return 0;
//}

int main() {
    map<int,string > m;
    m.insert(make_pair(0,"zero"));
    m.insert(make_pair(1,"one"));
    m.insert(make_pair(2,"two"));
    m.insert(make_pair(3,"three"));
    m.insert(make_pair(4,"four"));
    m.insert(make_pair(5,"five"));
    m.erase(m.find(0));
    cout <<m.size();
//    for (int i = 0; i < 6; ++i) {
//        cout << m[i] << endl;
//    }
}