//
// Created by GOD婴宁 on 2024/4/22.
//
#include "globalFile.h"
using namespace std;

int main() {
    int choice = 0;
    do {
        system("cls");
        mainMenu();
        choice = readMenuSelection(4);
        switch (choice) {
            case 1:
                loginIn(STUDENT_FILE, 1);
                break;
            case 2:
                loginIn(TEACHER_FILE, 2);
                break;
            case 3:
                loginIn(ADMIN_FILE, 3);
                break;
            case 0:
                exitSystem();
                break;
            default:
                break;
        }
    } while (choice);
    return 0;
}