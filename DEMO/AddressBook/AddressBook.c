//
// Created by GOD婴宁 on 2023/4/21.
//

#include "AddressBook.h"

//函数实现
//初始化通讯录
void Initialize(Contact *ps) {
    ps->data = (PeoInfo *) malloc(DEFAULT_SZ * sizeof(PeoInfo));//刚开始人数为5
    if (ps->data == NULL) {
        printf("在堆区分配内存失败，请再次尝试");
        return;
    }
    ps->count = 0;
    ps->capacity = DEFAULT_SZ;
    //加载文件中通讯录的数据到程序中
    LoadContact(ps);
}

//检查通讯录是否满员
void CheckCapacity(Contact *ps) {
    if (ps->count == ps->capacity) {//满了，capacity增加并扩员
        //扩员
        PeoInfo *ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(PeoInfo));
        if (ptr != NULL) {
            ps->data = ptr;
            ps->capacity += INCREASE_SZ;//每次增容5个人
            printf("已满员,增容成功\n");
        } else {
            printf("无内存分配,增容失败\n");
        }
    }
}

//读取联系人
void LoadContact(Contact *ps) {
    PeoInfo temp = {0};
    //打开文件
    FILE *pfRead = fopen("AddressBook.dat", "r");
    //判断打开情况一
    if (pfRead == NULL) {
        perror("LoadContact");//perror函数读取错误信息
        return;
    }
    //判断打开情况二
//    if (pfRead == NULL)
//    {
//        printf("LoadContact::%s\n", strerror(errno));//strerror函数读取错误信息
//        return;
//    }
    //读取文件
    while (fread(&temp, sizeof(PeoInfo), 1, pfRead)) {
        CheckCapacity(ps);
        ps->data[ps->count] = temp;
        ps->count++;
    }
    //关闭文件
    fclose(pfRead);
    pfRead = NULL;
}

//增加联系人
void Add(Contact *ps) {
    //判断人员是否满了
    CheckCapacity(ps);
    //没满，正常增加
    printf("请输入姓名：");
    scanf("%s", ps->data[ps->count].name);
    printf("请输入年龄：");
    scanf("%d", &(ps->data[ps->count].age));
    printf("请输入性别：");
    scanf("%s", ps->data[ps->count].gender);
    printf("请输入电话：");
    scanf("%s", ps->data[ps->count].telephone);
    printf("请输入地址：");
    scanf("%s", ps->data[ps->count].address);
    ps->count++;
    printf("添加成功!\n\n");
}

//显示联系人的信息
void Show(const Contact *ps) {
    if (ps->count == 0) {
        printf("通讯录为空!!\n");
    } else {
        int i = 0;
        printf("%-10s\t%-6s\t%-4s\t%-15s\t%-30s\n", "姓名", "年龄", "性别", "电话", "地址");
        for (i = 0; i < ps->count; i++) {
            printf("%-10s\t%-6d\t%-4s\t%-15s\t%-30s\n",
                   ps->data[i].name,
                   ps->data[i].age,
                   ps->data[i].gender,
                   ps->data[i].telephone,
                   ps->data[i].address
            );
        }
        printf("\n");
        printf("\n");
    }
}

//通过查找名字来确定人员是否存在,存在返回下标,不存在返回-1;
static int FindByName(const Contact *ps, char name[]) {
    int i = 0;
    for (i = 0; i < ps->count; i++) {
        if (0 == strcmp(ps->data[i].name, name)) {
            return i;
        }
    }
    return -1;
}

//删除联系人
void Delete(Contact *ps) {
    char name[MAX_NAME];
    int pos = 0;
    printf("请输入要删除人的姓名:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("要删除的人不存在!!\n\n");
    } else {
        int j = 0;
        for (j = pos; j < ps->count - 1; j++) {
            ps->data[j] = ps->data[j + 1];
        }
        ps->count--;
        printf("删除成功!!\n\n");
    }
}

//销毁通讯录
void DestroyContact(Contact *ps) {
    free(ps->data);
    ps->data = NULL;
}

//修改联系人的信息
void Modify(Contact *ps) {
    if (ps->count == 0) {
        printf("通讯录为空!!!\n\n");
        return;
    }
    char name[MAX_NAME];
    int pos = 0;
    printf("请输入要修改人的姓名:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("查无此人,修改失败!\n");
    } else {
        printf("请输入修改名字:");
        scanf("%s", ps->data[pos].name);
        printf("请输入修改年龄:");
        scanf("%d", &(ps->data[pos].age));
        printf("请输入修改性别:");
        scanf("%s", ps->data[pos].gender);
        printf("请输入修改电话:");
        scanf("%s", ps->data[pos].telephone);
        printf("请输入修改地址:");
        scanf("%s", ps->data[ps->count].address);
        printf("修改成功-.-\n");
    }
}

//只能查找到第一个符合条件的名字
void Search(Contact *ps) {
    char name[MAX_NAME];
    int pos = 0;
    printf("请输入要查找人的姓名:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("查无此人!!!\n");
    } else {
        printf("%-10s\t%-6s\t%-4s\t%-15s\t%-30s\n", "姓名", "年龄", "性别", "电话", "地址");
        printf("%-10s\t%-6d\t%-4s\t%-15s\t%-30s\n",
               ps->data[pos].name,
               ps->data[pos].age,
               ps->data[pos].gender,
               ps->data[pos].telephone,
               ps->data[pos].address
        );
    }
}

//保存通讯录数据到文件
void SaveContact(Contact *ps) {
    //打开文件
    FILE *pfWrite = fopen("AddressBook.dat", "w");
    if (NULL == pfWrite) {
        perror("SaveContact");
        return;
    }
    //写文件
    //方式一:
    int i = 0;
    for (i = 0; i < ps->count; ++i) {
        fwrite(ps->data + i, sizeof(PeoInfo), 1, pfWrite);
    }
    //方式二:
//    fwrite(ps->data,sizeof(PeoInfo),ps->count,pfWrite);
    //关闭文件
    fclose(pfWrite);
    pfWrite = NULL;
}

//以名字排序通讯录(采用冒泡排序)
void SortContact(Contact *ps) {
    if (ps->count == 0 || ps->count == 1) {
        printf("无需排序！！！\n");
        return;
    }
    int i, j;
    int flag = 0;
    PeoInfo temp = {0};
    for (i = 0; i < ps->count - 1; ++i) {
        flag = 1;
        for (j = 0; j < ps->count - 1; j++) {
            if (strcmp((ps->data + j)->name, (ps->data + j + 1)->name) > 0) {
                temp = *(ps->data + j);
                *(ps->data + j) = *(ps->data + j + 1);
                *(ps->data + j + 1) = temp;
                flag = 0;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    printf("排序完成！！！\n");
}





















