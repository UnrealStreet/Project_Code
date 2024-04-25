//
// Created by GOD婴宁 on 2023/5/8.
//
//顺序表（动态分布）的创建，操作等方法
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT 10
#define ADD 10
typedef struct {
    int *data;
    int length;
    int Maxsize;
} list;
list test = {0};

//初始化表
void InitList(list *l) {
    l->data = (int *) malloc(sizeof(int) * DEFAULT);
    if (l->data == NULL) {
        perror("InitList:");
        return;
    }
    l->length = 0;
    l->Maxsize = DEFAULT;
}

//扩充容量
void AddSizelist(list *l) {
    //创建临时表
    int *temp = l->data;
    //增加现有表长度
    l->data = (int *) malloc(sizeof(int) * (DEFAULT + ADD));
    l->Maxsize = DEFAULT + ADD;
    for (int i = 0; i < l->length; ++i) {
        l->data[i] = temp[i];
    }
    free(temp);
}

//插入表元素 成功返回1，失败返回-1
int ListInsert(list *l, int i, int Element) {
    if (i < 1 || i > l->length + 1) {
        return -1;
    }
    if (l->length >= l->Maxsize) {
        AddSizelist(l);
    }
    for (int j = l->length; j >= i; --j) {
        l->data[j] = l->data[j - 1];
    }
    l->data[i - 1] = Element;
    l->length++;
    return 1;
}

//删除表元素 成功返回删除的值，失败返回-1
int ListDelete(list *l, int i, int *Delete) {
    if (i < 1 || i > l->length) {
        return -1;
    }
    *Delete = l->data[i - 1];
    for (int j = i; j < l->length + 1; ++j) {
        l->data[j - 1] = l->data[j];
    }
    return *Delete;
}

//按位查找表元素 成功返回位对应的值，失败返回-1
int ListLocate(list *l, int i) {
    if (i < 1 || i > l->length) {
        return -1;
    }
    return l->data[i - 1];
}

//增加表元素
void ListSet(list *l, int Element) {
    l->data[l->length++] = Element;
}

//删除指定值后重新排列（时间复杂度O(n)）成功返回1，失败返回-1
int ListDeleteAll(list *l, int Delete) {
    if (l == NULL || l->length == 0) {
        return -1;
    }
    int i;
    int mark = 0;//标记需要前移的大小
    for (i = 0; i < l->length; ++i) {//一次遍历并进行前移
        if (l->data[i] == Delete) {
            mark++;//找到指定元素并进行计数
        } else {
            l->data[i - mark] = l->data[i];//扫描到非指定元素并进行前移
        }
    }
    l->length -= mark;//设置顺序表长度
    return 1;
}

//删除有序顺序表中重复的元素并进行前移（时间复杂度O(n)）成功返回1，失败返回-1
int ListDeleteRepeat(list *l) {
    if (l == NULL || l->length == 0) {
        return -1;
    }
    int i;
    int mark = 0;//标记需要前移的大小
    int temp = l->data[0];//标记需要对比的数值
    for (i = 1; i < l->length; i++) {
        if (l->data[i] == temp) {
            mark++;
        } else {
            temp = l->data[i];
            l->data[i - mark] = l->data[i];
        }
    }
    l->length -= mark;//设置顺序表长度
    return 1;
}

//打印顺序表的元素内容
void ListPrint(list *l) {
    for (int i = 0; i < l->length; ++i) {
        printf("%d ", l->data[i]);
    }
}

//销毁顺序表
void ListDestroy(list *l) {
    free(l->data);
    l->data = NULL;
}

//逆置指定范围的元素,这里的范围是位序,即1——顺序表长度
//typedef int ElemData 避免操作其他数据类型时重复修改-可以参考此方法
void reverse(list *l, int from, int to) {
    if (l == NULL || from < 1 || to > l->length) {
        return;
    }
    int mid = (from + to) / 2;
    int temp;
    for (int i = from - 1; i < mid; ++i) {
        temp = l->data[i];
        l->data[i] = l->data[to - 1];
        l->data[to - 1] = temp;
        to--;
    }
}

//循环往前移动p个元素
void converse(list *l, int num) {
    reverse(l, 1, l->length);
    reverse(l, 1, l->length - num);
    reverse(l, (l->length - num) + 1, l->length);
}

int main() {
    //创建表
    list l;
    list *list = &l;
    InitList(list);
    ListSet(list, 1);
    ListSet(list, 15);
    ListSet(list, 6);
    ListSet(list, 12);
    ListSet(list, 7);
    ListSet(list, 9);
    ListSet(list, 1);
    ListSet(list, 2);
    ListSet(list, 5);

    converse(list, 5);
    ListPrint(list);
    return 0;
}

//链表方法
typedef struct ListNode {
    int val;
    struct ListNode *next;
} LNode, *List;


//删除链表的倒数第 N 个结点
struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    if (head == NULL) {
        return head;
    }
    struct ListNode *temp = head, *temp1;
    int lenList = 0, Delete;
    while (temp != NULL) {
        lenList++;
        temp = temp->next;
    }
    Delete = lenList - n + 1;
    temp = head;
    if (Delete == 1) {
        head = temp->next;
        free(temp);
    } else {
        for (int i = 2; i < Delete; ++i) {
            temp = temp->next;
        }
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
    }
    return head;
}

//反转链表中的中间部分
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    LNode *headnode = (LNode *) malloc(sizeof(LNode));
    headnode->val = -1;
    headnode->next = head;
    LNode *p, *r, *q;
    p = headnode;
    for (int i = 0; i < left - 1; ++i) {
        p = p->next;//p暂时为转换前的第一个结点
    }
    r = p->next;//工作指针
    p->next = NULL;
    for (int i = 0; i <= right - left && r->next != NULL; ++i) {
        q = r->next;//暂存r的下一个结点
        r->next = p->next;//将r插在p之后
        p->next = r;
        r = q;
    }
    return headnode->next;
}