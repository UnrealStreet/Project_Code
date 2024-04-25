//
// Created by GOD婴宁 on 2023/4/21.
//
#include "AddressBook.h"

//菜单选项
void menu() {
    printf("\t简易通讯录\t\n");
    printf("1.增加联系人\t2.删除联系人\n");
    printf("3.更改联系人\t4.查找联系人\n");
    printf("5.显示联系人\t6.排序联系人\n");
    printf("7.保存通讯录\t0.退出程序\n");
    printf("请选择所需功能：");
}
//主函数,调用程序
int main() {
    int input = 0;
    Contact con;//创建一个通讯录，con是通讯录，里面包含存放的人员信息，数量，最大容量
    //初始化联系录并且加载dat文件
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
                printf("保存成功！！！\n");
                break;
            case EXIT:
                SaveContact(&con);
                DestroyContact(&con);
                printf("退出通讯录-.-");
                break;
            default:
                printf("选择错误！！请重新输入!\n");
                break;
        }
    } while (input);
    return 0;
}