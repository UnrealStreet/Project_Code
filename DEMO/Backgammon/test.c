//
// Created by GOD婴宁 on 2023/4/10.
//
#include "Backgammon.h"

//开始界面
void menu() {
    printf("*****************************\n");
    printf("*****GAME OF BACKGAMMON******\n");
    printf("****** 1.play   0.exit*******\n");
    printf("*****************************\n");
}

//设置游戏
void game() {
//设置雷的信息的棋盘
    char Hide[ROWS][COLS] = {'0'};
//展示给用户操作的棋盘
    char Show[ROWS][COLS] = {'0'};
//初始化棋盘
    initialboard(Hide, ROWS, COLS, '0');
    initialboard(Show, ROWS, COLS, '*');
//显示棋盘
//    DispalyBoard(Hide, ROW, COL);//显示初始化的棋盘
    printf("\n");
    DispalyBoard(Show, ROW, COL);
//设置雷的数量及位置
    SetMine(Hide, ROW, COL);
    //查看雷的位置
//    DispalyBoard(Hide, ROW, COL);
//扫雷
    FindMine(Hide, Show, ROW, COL);
}

void test() {
    int input = 0;
    srand((unsigned int) time(NULL));
        menu();
        printf("请选择：");
        scanf("%d", &input);
    do {
        switch (input) {
            case 0:
                break;
            case 1:
                game();
                printf("是否继续游戏（0/1)：");
                scanf("%d", &input);
                break;
            default:
                printf("选择错误，请重新选择！\n");
        }
    } while (input);
}


int main() {
    test();
    return 0;
}