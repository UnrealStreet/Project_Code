//
// Created by GOD婴宁 on 2024/4/17.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class compare {
public:
    vector<double> v1;
    vector<double> v2;

    void compare_data();
};

void compare::compare_data() {
    double s;
    cout << "请输入第一次的数据：" << endl;
    while (cin >> s) {
        v1.push_back(s);
    }
    // 清空输入缓冲区
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "请输入第二次的数据：" << endl;
    while (cin >> s) {
        v2.push_back(s);
    }
    int v1_size = v1.size();
    int v2_size = v2.size();
    s = v1_size < v2_size ? v1_size : v2_size;
    bool is_same = true;
    int diff_sum = 0; // 记录不同的天数
    double diff = 0;// 记录总差值
    cout << "\n对比结果如下：" << endl;
    for (int i = 0; i < s; ++i) {
        if (v1[i] != v2[i]) {
            cout << "第" << 1 + i << "日:\t" << v1[i] << " - " << v2[i]
                 << "\t差别为：" << v1[i] - v2[i] << endl;
            is_same = false;
            diff += v1[i] - v2[i];
            diff_sum++;
        }
    }
    if (is_same)
        cout << "两个数据源相同" << endl;
    else
        cout << "总共有" << diff << "个数据不同,总差额为：" << diff << endl;
    cout << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    compare c;
    do {
        c.compare_data();
        cout << "是否继续对比数据？(y/n)" << endl;
        char a;
        cin >> a;
        if (a == 'y') {
            c.v1.clear();
            c.v2.clear();
        } else
            break;
    } while (true);
    return 0;
}