//
// Created by GOD婴宁 on 2024/4/16.
//
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <algorithm>

using namespace std;

class player {
public:
    double score;
    string name;

    player(double score, string name) : score(score), name(name) {}

};

void creatPlayers(vector<player> &v, int nums) {
    string nameSeed("ABCDEFG");
    for (int i = 0; i < nums; ++i) {
        string name = "选手";
        name += nameSeed.at(i);
        player p(0, name);
        v.push_back(p);
    }
}


int randomNum() {
    int score = rand() % 41 + 60;  // 60 ~ 100
    return score;// 输出随机数
}

void playerScore(vector<player> &v) {

    for (auto it = v.begin(); it != v.end(); it++) {
        deque<double> s;
        for (int i = 0; i < 10; ++i) {
            int num = randomNum();
            s.push_back(num);
        }
        sort(s.begin(), s.end());
        s.erase(s.begin());
        s.erase(s.end() - 1);
        double sum = 0;
        for (auto it = s.begin(); it != s.end(); it++) {
            sum += *it;
        }
        double average = sum / s.size();
        it->score =average;
    }
}

void printPlayerScore(const vector<player> &v) {
    for (const auto & it : v) {
        cout << it.name << "的成绩为：" << it.score << endl;
    }
}

int main() {
    vector<player> v;
    srand((unsigned int)time(nullptr));
    creatPlayers(v, 5);

    playerScore(v);

    printPlayerScore(v);
    cin.get();
    return 0;
}