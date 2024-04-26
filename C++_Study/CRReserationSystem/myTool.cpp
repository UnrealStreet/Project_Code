//
// Created by GOD婴宁 on 2024/4/23.
//

#include "myTool.h"

int readMenuSelection(int choice) {
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || message[0] - '0' < 0 || message[0] - '0' >= choice)
            cout << "输入错误，请重新输入：";
        else
            break;
    }
    int ans = message[0] - '0';
    //输入正确
    return ans;
}
//int readMenuSelection(int choice,int) {
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    string message;
//    //进行合法性校验
//    while (true) {
//        getline(cin, message);
//        if (message.size() != 1 || message[0] - '0' < 0 || message[0] - '0' >= choice)
//            cout << "输入错误，请重新输入：";
//        else
//            break;
//    }
//    int ans = message[0] - '0';
//    //输入正确
//    return ans;
//}

void exitSystem() {
    cout << "\t\t欢迎下次使用！！！" << endl;
    //1.设置绘图边界
    double a = 0.64;
    double bound = 1.3 * sqrt(a);
    //2.开始制图
    //x,y 坐标
    double step = 0.05;//步长
    for (double y = bound; y >= -bound; y -= 2 * step) {
        for (double x = -bound; x <= bound; x += step) {
            double result = pow((pow(x, 2) + pow(y, 2) - a), 3) - pow(x, 2) * pow(y, 3);
            if (result <= 0)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
    system("timeout /t 1 /nobreak > NUL");
}

//调用前没有任何输入的等待
void waitConfirm() {
    cout << "请按回车键以继续...";
    string message;
    getline(cin, message); //防止直接退出
}

//调用前有输入的等待
void waitConfirm(int) {
    cout << "请按回车键以继续...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string message;
    getline(cin, message); //防止直接退出
}

//确任信息
char readQuitConfirm() {
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || (toupper(message[0]) != 'Y' && toupper(message[0]) != 'N'))
            cout << "输入错误，请重新输入（Y/N）：";
        else
            break;
    }
    //输入正确
    return toupper(message[0]);
}

pair<int,string> selectTime() {
        map<int,string> num_to_chinese = {
                {1, "一"},
                {2, "二"},
                {3, "三"},
                {4, "四"},
                {5, "五"}
        };
    // 获取当前时间
    auto now = chrono::system_clock::now();
    // 获取当前是星期几
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm tm{};
    localtime_s(&tm, &now_time_t);
    int wday = tm.tm_wday; // 0-6 对应周日到周六

    // 计算到周五需要的天数
    int days_to_friday = (5 - wday) % 7;
    int i = 1;
    if (days_to_friday == 0) {
        days_to_friday = 7; // 如果今天就是周五，那么输出下周的周一至周五
        wday = 0;
        i = 3;
    }
    ostringstream oss;// 字符串输出流
    int num = 0;
    for (; i <= days_to_friday; ++i) {
        ++wday;// 周几
        // 添加一天的时间
        auto next_day = now + chrono::hours(24 * i);

        // 将时间点转换为时间_t
        time_t next_day_time_t = chrono::system_clock::to_time_t(next_day);

        // 将时间_t转换为日期字符串
        localtime_s(&tm, &next_day_time_t);

        // 按照 "月日" 的格式打印日期
        oss << ++num << "." << put_time(&tm, "%m月%d日")
            << "(周" << num_to_chinese[wday] << ")" << endl;
    }
    cout << oss.str();
    string s = oss.str();
    pair<int,string> p = {num,s};
    return p;
}

 // 取出的特定数字后的日期
string getTime(const string& s,int target_num) {
    istringstream iss(s);
    string line;
    string date;
    while (getline(iss, line, '\n')) {
        int num = stoi(line.substr(0, line.find('.')));
        if (num == target_num) {
            size_t first_dot = line.find('.');
            size_t last_dot = line.rfind(')');
            date = line.substr(first_dot + 1, last_dot - first_dot);
            break;
        }
    }
    return date;
}