//
// Created by GOD婴宁 on 2023/5/12.
//
//串的定义及相关方法
#include <stdio.h>

typedef struct String {
    char *data;
    int length;
} String;

//字符串匹配模式
//1.朴素匹配算法
int SimpleMatch(int local, String MString, String TString) {
    int i;
    int j;
    for (i = 1, j = 1; i <= MString.length - TString.length + 1 && j <= TString.length;) {
        if (MString.data[i] == TString.data[j]) {
            i++;
            j++;
        } else {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > TString.length) {
        return i - j + 1;
    }
    return 0;
}

//kMP搜索算法(主要需算出next数组)next数组可以手算，可以尝试用代码实现
int Kmp(int local, String MString, String TString, const int next[]) {
    int i;
    int j;
    for (i = 1, j = 1; i <= MString.length && j <= TString.length;) {
        if (j == 0 || MString.data[i] == TString.data[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j > TString.length) {
        return i - j + 1;
    }
    return 0;
}

//对于KMP算法中的next数组优化为nextval数组
int *NextOptimize(String T, int next[]) {
    int *nextval = next;
    nextval[1] = 0;
    for (int i = 2; i <= T.length; ++i) {
        if (T.data[i] == T.data[next[i]]) {
            nextval[i] = nextval[next[i]];
        } else {
            nextval[i] = next[i];
        }
    }
    return nextval;
}

//kMP优化搜索算法-采用nextval数组，即根据next数组求出nextval数组
int KmpOptimize(int local, String MString, String TString, const int nextval[]) {
    int i;
    int j;
    for (i = 1, j = 1; i <= MString.length && j <= TString.length;) {
        if (j == 0 || MString.data[i] == TString.data[j]) {
            i++;
            j++;
        } else {
            j = nextval[j];
        }
    }
    if (j > TString.length) {
        return i - j + 1;
    }
    return 0;
}