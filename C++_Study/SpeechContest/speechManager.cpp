//
// Created by GOD婴宁 on 2024/4/21.
//

#include "speechManager.h"
#include <random>
#include <chrono>

#define judges 10

SpeechManager::SpeechManager() {
    initSpeech();
    createSpeaker();
    loadRecord();
}

SpeechManager::~SpeechManager()=default;

void SpeechManager::showMenu() {
    cout << "********************************************" << endl;
    cout << "*************  欢迎参加演讲比赛 ************" << endl;
    cout << "*************  1.开始演讲比赛  *************" << endl;
    cout << "*************  2.查看往届记录  *************" << endl;
    cout << "*************  3.清空比赛记录  *************" << endl;
    cout << "*************  0.退出比赛程序  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void SpeechManager::initSpeech() {
    this->player.resize(3);
    player[0].clear();
    player[1].clear();
    player[2].clear();
    this->speakers.clear();
    this->record.clear();
    this->round = 1;
}

void SpeechManager::exitSystem() {
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
}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    int size = (int) nameSeed.size();
    for (int i = 0; i < size; i++) {
        string name = "选手";
        name += nameSeed[i];
        Speaker sp;
        sp.setName(name);
        for (int j = 0; j < 2; j++) {
            sp.setScore(0, j);
        }
        this->player[0].push_back(i + 10001);
        this->speakers.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech() {
    //第一轮比赛
    //1.抽签
    speechDraw();
    //2.比赛
    speechContest();
    //3.显示晋级结果
    showScore();
    //第二轮比赛
    this->round++;
    //1.抽签
    speechDraw();
    //2.比赛
    speechContest();
    //3.显示最终结果
    showScore();
    //4.保存分数
    saveRecord();
    //5.重置比赛
    initSpeech();
    createSpeaker();
    loadRecord();
    cout << "本届比赛完满结束！！！" << endl;
    waitConfirm();
}

void SpeechManager::speechDraw() {
    cout << "第 << " << this->round << " >> 轮比赛选手正在抽签\n" << endl;
    cout << "抽签后演讲顺序如下：" << endl;
    if (this->round == 1) {
        shuffle(player[0].begin(), player[0].end(),
                std::mt19937(chrono::system_clock::now().time_since_epoch().count()));
        for (int &it: player[0]) {
            cout << it << " ";
        }
        cout << endl;
    } else {
        shuffle(player[1].begin(), player[1].end(),
                std::mt19937(chrono::system_clock::now().time_since_epoch().count()));
        for (auto it = player[1].begin(); it != player[1].end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void SpeechManager::speechContest() {
    // 获取当前时间的毫秒数
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed); // 使用当前时间作为种子初始化随机数生成器
    uniform_int_distribution<> dis(600, 1000); // 定义浮点数分布范围

    cout << "\n——————————————第" << round << "轮比赛正式开始——————————————" << endl;
    multimap<double, int, greater<>> groupScore;

    int num = 0;
    vector<int> storagePlayer;
    if (round == 1)
        storagePlayer = player[0];
    else
        storagePlayer = player[1];

    for (int s: storagePlayer) {
        num++;
        deque<double> d;
        for (int i = 0; i < judges; i++) {
            double score = dis(gen) / 10.; // 生成随机浮点数
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<>());
        d.pop_front();
        d.pop_back();
        double sum = accumulate(d.begin(), d.end(), 0.0);
        double avg = sum / double(d.size());
        speakers[s].setScore(avg, round - 1);//将生成的平均分放入对应选手的成绩中
        groupScore.insert(make_pair(avg, s));
        //按6人一组打印
        if (num % 6 == 0) {
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            for (auto &it: groupScore) {
                cout << "编号：" << it.second << "\t姓名：" << speakers[it.second].getName()
                     << "\t成绩：" << it.first << endl;
            }
            int count = 0;
            //存放晋升组成员
            for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
                if (round == 1)
                    player[1].push_back(it->second);
                else
                    player[2].push_back(it->second);
            }
            groupScore.clear();
            cout << endl;
        }
    }
    cout << "———————————————第" << round << "论比赛完毕！——————————————" << endl;
    waitConfirm();
}

void SpeechManager::showScore() {
    cout << "\n—————————————第" << round << "轮晋级选手信息如下—————————————" << endl;
    vector<int> v;
    if (round == 1)
        v = player[1];
    else
        v = player[2];
    for (int s: v) {
        cout << "选手编号：" << s << "\t姓名：" << speakers[s].getName()
             << "\t得分：" << speakers[s].getScore(round - 1) << endl;
    }
    cout << endl;
    waitConfirm();
    system("cls");
    showMenu();
}

void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "文件写入失败,未保存成功！！！" << endl;
        return;
    }

    for (auto it = player[2].begin(); it != player[2].end(); it++) {
        ofs << *it << "," << speakers[*it].getScore(1) << ",";
    }
    ofs << endl;
    ofs.close();
    cout << "比赛结果已经保存成功" << endl;
    fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
    ifstream ifs(FILENAME, ios::in);
    if (!ifs.is_open()) {
        fileIsEmpty = true;
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    //文件清空情况
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "文件数据为空" << endl;
        fileIsEmpty = true;
        ifs.close();
        return;
    }
    //文件不为空
    fileIsEmpty = false;
    ifs.putback(ch);//将读取的单个字符回退一位
    int tRound = 0;
    string data;
    while (ifs >> data) {
        vector<string> v;
        int pos = -1;
        int start = 0;
        while (true) {
            pos = (int) data.find(',', start);
            if (pos == -1)
                break;
            string temp = data.substr(start, pos - start);
            v.push_back(temp);
            start = pos + 1;
        }
        record.insert(make_pair(tRound, v));
        tRound++;
    }
    ifs.close();
}

void SpeechManager::showRecord() {
    if (fileIsEmpty) {
        cout << "文件不存在或数据为空" << endl;
    } else {
        for (int i = 0; i < (int) record.size(); ++i) {
            cout << "第" << i + 1 << "届比赛结果如下：\n"
                 << "冠军编号：" << record[i][0] << "\t得分：" << record[i][1] << "\n"
                 << "季军编号：" << record[i][2] << "\t得分：" << record[i][3] << "\n"
                 << "亚军编号：" << record[i][4] << "\t得分：" << record[i][5] << "\n" << endl;
        }
    }
    waitConfirm();
}

void SpeechManager::clearRecord() {
    cout << "是否确认清空所有数据？（Y/N）";
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || (toupper(message[0]) != 'Y' && toupper(message[0]) != 'N'))
            cout << "输入错误，请重新输入（Y/N）：";
        else
            break;
    }
    if (toupper(message[0]) == 'Y') {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        record.clear();
        loadRecord();
        cout << "清空成功！" << endl;
    } else {
        cout << "取消清空！" << endl;
    }
    waitConfirm();
}

//对speaker类的操作-----------------------------------------
const string &Speaker::getName() const {
    return name;
}

void Speaker::setName(const string &name) {
    this->name = name;
}

double Speaker::getScore(int location) const {
    return score[location];
}

void Speaker::setScore(double score, int location) {
    this->score[location] = score;
}


//自定义函数--------------------------------------
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

void waitConfirm() {
    cout << "请按回车键以继续...";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string message;
    getline(cin, message); //防止直接退出
}