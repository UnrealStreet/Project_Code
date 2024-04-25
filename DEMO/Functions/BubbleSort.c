//
// Created by GOD婴宁 on 2023/4/16.
//自己仿造<stdlib.h>中的qsort写的基于冒泡排序的所有类型排序方法
#include <stdio.h>
#include <string.h>

//原函数的具体内容：
//void __cdecl qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__cdecl *_PtFuncCompare)(const void *,const void *));
typedef struct Student {
    int age;
    char name[20];
} Student;

int compare_int(const void *data1, const void *data2) {
    return *(int *) data1 - *(int *) data2;
}

int compare_String(const void *data1, const void *data2) {
    return strcmp(((Student *) data1)->name, ((Student *) data2)->name);
}

void Swap(char *p1, char *p2, int size) {
    int i = 0;
    for (i = 0; i < size; ++i) {
        char temp = *(p1 + i);
        *(p1 + i) = *(p2 + i);
        *(p2 + i) = temp;
    }
}

void
BubbleSort(void *Base, int NumOfElements, int SizeOfElement, int (*compare_method)(const void *, const void *)) {
    int i = 0;
    int j = 0;
    int flag = 0;//判断是否进行了交换的标志
    for (i = 0; i < NumOfElements - 1; ++i) {
        flag = 1;//每一轮开始重置flag
        for (j = 0; j < NumOfElements - 1 - i; ++j) {
            if (compare_method((char *) Base + j * SizeOfElement, (char *) Base + (j + 1) * SizeOfElement) > 0) {
                Swap((char *) Base + j * SizeOfElement, (char *) Base + (j + 1) * SizeOfElement, SizeOfElement);
                flag = 0;//元素进行交换就改变flag
            }
        }
        if (flag) {//没有进行交换改变flag的话就退出循环
            break;
        }
    }
}

int main() {
    int i = 0;
    int j = 0;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    BubbleSort(arr, size, sizeof(arr[0]), compare_int);
    for (i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    Student stu[3] = {{18, "zhangsan"},
                      {20, "lisi"},
                      {19, "wangwu"}};
    int size1 = sizeof(stu) / sizeof(stu[0]);
    BubbleSort(stu, size1, sizeof(stu[0]), compare_String);
    for (j = 0; j < size1; ++j) {
        printf("%s ", stu[j].name);
    }
    return 0;
}
