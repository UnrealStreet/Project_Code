//
// Created by GODӤ�� on 2023/4/21.
//
#include "AddressBook.h"

//�˵�ѡ��
void menu() {
    printf("\t����ͨѶ¼\t\n");
    printf("1.������ϵ��\t2.ɾ����ϵ��\n");
    printf("3.������ϵ��\t4.������ϵ��\n");
    printf("5.��ʾ��ϵ��\t6.������ϵ��\n");
    printf("7.����ͨѶ¼\t0.�˳�����\n");
    printf("��ѡ�����蹦�ܣ�");
}
//������,���ó���
int main() {
    int input = 0;
    Contact con;//����һ��ͨѶ¼��con��ͨѶ¼�����������ŵ���Ա��Ϣ���������������
    //��ʼ����ϵ¼���Ҽ���dat�ļ�
    Initialize(&con);
//    Contact data = {0};
    do {
        menu();
        scanf("%d", &input);
        switch (input) {
            case ADD:
                Add(&con);
                break;
            case DELETE:
                Delete(&con);
                break;
            case MODIFY:
                Modify(&con);
                break;
            case SEARCH:
                Search(&con);
                break;
            case SHOW:
                Show(&con);
                break;
            case SORT:
                SortContact(&con);
                break;
            case SAVE:
                SaveContact(&con);
                printf("����ɹ�������\n");
                break;
            case EXIT:
                SaveContact(&con);
                DestroyContact(&con);
                printf("�˳�ͨѶ¼-.-");
                break;
            default:
                printf("ѡ����󣡣�����������!\n");
                break;
        }
    } while (input);
    return 0;
}