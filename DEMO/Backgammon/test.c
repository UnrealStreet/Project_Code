//
// Created by GODӤ�� on 2023/4/10.
//
#include "Backgammon.h"

//��ʼ����
void menu() {
    printf("*****************************\n");
    printf("*****GAME OF BACKGAMMON******\n");
    printf("****** 1.play   0.exit*******\n");
    printf("*****************************\n");
}

//������Ϸ
void game() {
//�����׵���Ϣ������
    char Hide[ROWS][COLS] = {'0'};
//չʾ���û�����������
    char Show[ROWS][COLS] = {'0'};
//��ʼ������
    initialboard(Hide, ROWS, COLS, '0');
    initialboard(Show, ROWS, COLS, '*');
//��ʾ����
//    DispalyBoard(Hide, ROW, COL);//��ʾ��ʼ��������
    printf("\n");
    DispalyBoard(Show, ROW, COL);
//�����׵�������λ��
    SetMine(Hide, ROW, COL);
    //�鿴�׵�λ��
//    DispalyBoard(Hide, ROW, COL);
//ɨ��
    FindMine(Hide, Show, ROW, COL);
}

void test() {
    int input = 0;
    srand((unsigned int) time(NULL));
        menu();
        printf("��ѡ��");
        scanf("%d", &input);
    do {
        switch (input) {
            case 0:
                break;
            case 1:
                game();
                printf("�Ƿ������Ϸ��0/1)��");
                scanf("%d", &input);
                break;
            default:
                printf("ѡ�����������ѡ��\n");
        }
    } while (input);
}


int main() {
    test();
    return 0;
}