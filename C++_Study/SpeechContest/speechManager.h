//
// Created by GOD婴宁 on 2024/4/21.
//
#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

#define FILENAME "F:\\Project_Code\\C++_Study\\SpeechContest\\speech.csv"
using namespace std;

enum choice {
    EXIT,
    START,
    VIEW,
    CLEAR
};

class Speaker {
private:
    string name;
    double score[2];
public:
    [[nodiscard]] const string &getName() const;

    void setName(const string &name);

    void setScore(double score, int location);

    [[nodiscard]] double getScore(int location) const;
};

//--------------------------------------------------

class SpeechManager {
public:
    vector<vector<int>> player;
    map<int, Speaker> speakers;
    map<int, vector<string>> record;
    int round;
    bool fileIsEmpty;

    SpeechManager();

    ~SpeechManager();

    static void showMenu();

    static void exitSystem();

    void initSpeech();

    void createSpeaker();

    void startSpeech();

    void speechDraw();

    void speechContest();

    void showScore();

    void saveRecord();

    void loadRecord();

    void showRecord();

    void clearRecord();
};


//自制通用类函数
int readMenuSelection(int choice);

void waitConfirm();