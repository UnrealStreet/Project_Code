//
// Created by GOD婴宁 on 2023/4/21.
//

#ifndef DEMO_ADDRESSBOOK_H
#define DEMO_ADDRESSBOOK_H

#define MAX_NAME 10
#define MAX_GENDER 5
#define MAX_TELEPHONE 14
#define MAX_ADDRESS 30
#define DEFAULT_SZ 5
#define INCREASE_SZ 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//选项枚举类代替数字0-6
enum Option {
    EXIT,
    ADD,
    DELETE,
    MODIFY,
    SEARCH,
    SHOW,
    SORT,
    SAVE
};
//定义人员基本信息
typedef struct PeoInfo {
    char name[MAX_NAME];
    int age;
    char gender[MAX_GENDER];
    char telephone[MAX_TELEPHONE];
    char address[MAX_ADDRESS];
} PeoInfo;
//定义通讯录
typedef struct Contact {
    PeoInfo *data;//动态存放联系人信息
    int count;//记录当前联系人数量
    int capacity;//记录当前最大容量
} Contact;

//声明函数
void Initialize(Contact *ps);

//增加一个联系人到通讯录
void Add(Contact *ps);

//展示通讯录
void Show(const Contact *ps);

//删除一个联系人
void Delete(Contact *ps);

//修改当前联系人
void Modify(Contact *ps);

//销毁通讯录
void DestroyContact(Contact *ps);

//查找联系人
void Search(Contact *ps);

//保存通讯录
void SaveContact(Contact *ps);

//排序通讯录
void SortContact(Contact *ps);

//加载文件中通讯录的数据到程序中
void LoadContact(Contact *ps);

#endif //DEMO_ADDRESSBOOK_H
