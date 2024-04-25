//
// Created by GOD婴宁 on 2023/10/23.
//
/*
1.顺序查找-适用于线性表
哨兵写法（数组从下标为1开始存储）
优点：不需要判断是否越界
*/
int SequentialSearch(int arr[], int target, int arrlen) {
    arr[0] = target;
    int i;
    for ( i = arrlen-1;arr[i] !=target  ; i--) {
    }
    return i;
}

