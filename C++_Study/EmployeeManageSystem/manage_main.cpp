//
// Created by GOD婴宁 on 2024/4/10.
//
#include "workerManager.h"
#include "worker.h"


int main() {
    WorkerManger wm;
    wm.loadFile();
    int choice = 0;
    do {
        system("cls");
        wm.show_Menu();
        choice = readMenuSelection(8);
        switch (choice) {
            case ADD:
                wm.addWorker();
                break;
            case SHOW:
                wm.showWorker();
                break;
            case DELETE:
                wm.deleteWorker();
                break;
            case MODIFY:
                wm.modifyWorker();
                break;
            case SEARCH:
                wm.searchWorker();
                break;
            case SORT:
                wm.sortWorker();
                break;
            case CLEAR:
                wm.clearFile();
                break;
            case Exit:
                cout << "\n\t\t欢迎下次使用！" << endl;
                wm.exitSystem();
                system("timeout /t 1 /nobreak > NUL");
                break;
            default:
                break;
        }
    } while (choice);
    return 0;
}
