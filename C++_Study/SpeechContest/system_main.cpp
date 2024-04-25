//
// Created by GOD婴宁 on 2024/4/21.
//
#include "speechManager.h"

int main() {
    SpeechManager sm;
    int choice;
    do {
        system("cls");
        SpeechManager::showMenu();
        cout << "请输入您的选择：";
        choice = readMenuSelection(4);
        switch (choice) {
            case START:
                sm.startSpeech();
                break;
            case VIEW:
                sm.showRecord();
                break;
            case CLEAR:
                sm.clearRecord();
                break;
            case EXIT:
                cout << "\n\t\t欢迎下次使用！" << endl;
                SpeechManager::exitSystem();
                system("timeout /t 1 /nobreak > NUL");
                break;
            default:
                break;
        }
    } while (choice);
    return 0;
}