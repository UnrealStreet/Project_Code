//
// Created by GODӤ�� on 2023/4/10.
//
#include "Backgammon.h"

void initialboard(char board[ROWS][COLS], int row, int col, char set) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            board[i][j] = set;
        }
    }
}

void DispalyBoard(char board[ROWS][COLS], int row, int col) {
    int i;
    for (i = 0; i <= col; ++i) {
        printf("%d  ", i);
    }
    printf("\n");
    for (i = 1; i <= row; ++i) {
        printf("%d  ", i);
        for (int j = 1; j <= col; ++j) {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }
}

void SetMine(char board[ROWS][COLS], int row, int col) {
    int x = 0;
    int y = 0;
    int mines = GAME_EASY;
    while (mines) {
        x = rand() % row + 1;
        y = rand() % col + 1;
        if (board[x][y] == '0') {
            board[x][y] = '1';
            mines--;
        }
    }
}

int get_Hide_Count(char board[ROWS][COLS], int x, int y) {
    return board[x - 1][y] +
           board[x - 1][y - 1] +
           board[x][y - 1] +
           board[x + 1][y - 1] +
           board[x + 1][y] +
           board[x + 1][y + 1] +
           board[x][y + 1] +
           board[x - 1][y + 1] - 8 * '0';
}

/*void diffusion(char Show[ROWS][COLS], char Hide[ROWS][COLS], int x, int y) {
    if (get_Hide_Count(Hide, x - 1, y) == 0) {
        Show[x - 1][y] = ' ';
        diffusion(Show, Hide, x - 1, y);
    } else {
        Show[x - 1][y] = get_Hide_Count(Show, x - 1, y) + '0';
    }
    if (get_Hide_Count(Hide, x - 1, y - 1) == 0) {
        Show[x - 1][y - 1] = ' ';
        diffusion(Show, Hide, x - 1, y - 1);
    } else {
        Show[x - 1][y - 1] = get_Hide_Count(Show, x - 1, y - 1) + '0';
    }
    if (get_Hide_Count(Hide, x, y - 1) == 0) {
        Show[x][y - 1] = ' ';
        diffusion(Show, Hide, x, y - 1);
    } else {
        Show[x][y - 1] = get_Hide_Count(Show, x, y - 1) + '0';
    }
    if (get_Hide_Count(Hide, x + 1, y - 1) == 0) {
        Show[x + 1][y - 1] = ' ';
        diffusion(Show, Hide, x + 1, y - 1);
    } else {
        Show[x + 1][y - 1] = get_Hide_Count(Show, x + 1, y - 1) + '0';
    }
    if (get_Hide_Count(Hide, x + 1, y) == 0) {
        Show[x + 1][y] = ' ';
        diffusion(Show, Hide, x + 1, y);
    } else {
        Show[x + 1][y] = get_Hide_Count(Show, x + 1, y) + '0';
    }
    if (get_Hide_Count(Hide, x + 1, y + 1) == 0) {
        Show[x + 1][y + 1] = ' ';
        diffusion(Show, Hide, x + 1, y + 1);
    } else{
        Show[x + 1][y + 1] = get_Hide_Count(Show, x + 1, y + 1)+'0';
    }
    if (get_Hide_Count(Hide, x, y + 1) == 0) {
        Show[x][y + 1] = ' ';
        diffusion(Show, Hide, x, y + 1);
    }else{
        Show[x ][y + 1] = get_Hide_Count(Show, x , y + 1)+'0';
    }
    if (get_Hide_Count(Hide, x - 1, y + 1) == 0) {
        Show[x - 1][y + 1] = ' ';
        diffusion(Show, Hide, x - 1, y + 1);
    }else{
        Show[x - 1][y + 1] = get_Hide_Count(Show, x - 1, y + 1)+'0';
    }
}*/


void FindMine(char Hide[ROWS][COLS], char Show[ROWS][COLS], int row, int col) {
    int x = 0;
    int y = 0;
    int count = 0;
    int win = 0;
    while (win < row * col - GAME_EASY) {
        printf("�������Ų��׵����꣺");
        scanf("%d %d", &x, &y);
        if (x > 0 && x <= row && y > 0 && y <= col) {//�ж������Ƿ���ȷ
            //����
            if (Hide[x][y] == '1') {
                printf("���ź�����Ϸ����\n");
                DispalyBoard(Hide, row, col);
                printf("\n");
                break;
            } else {//������
                //�����������Χ�м�����
                count = get_Hide_Count(Hide, x, y);
                //����Χû���׵�λ�ý�����ɢ
//                if (0 == count) {
//                    diffusion(Show, Hide, x, y);
//                }
                Show[x][y] = count + '0';
                DispalyBoard(Show, row, col);
                win++;
            }
        } else {
            printf("���������������������룡\n");
        }
    }
    if (win == row * col - GAME_EASY) {
        printf("��ϲ�㣬���׳ɹ�������\n");
        DispalyBoard(Hide, row, col);
        printf("\n");
    }
}

