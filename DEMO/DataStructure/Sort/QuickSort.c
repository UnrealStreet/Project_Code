//
// Created by GOD婴宁 on 2023/5/29.
//
//快速排序的实现代码
//基于顺序表

//用第一个元素将待排序序列划分成左右两个部分
int Partition(int a[], int low, int high) {
    int pivot = a[low];//第一个元素作为枢轴
    while (low < high) {//用low、high搜索枢轴的最终位置
        while (low < high && a[high] >= pivot) {//从最后往前找到小于枢轴的第一元素
            --high;
        }
        a[low] = a[high];//将其移动到左侧
        while (low < high && a[low] <= pivot) {//从前往后找到大于枢轴的第一元素
            ++low;
        }
        a[high] = a[low];//将其移动到右侧
    }
    a[low] = pivot;//枢轴元素存到最终位置
    return low;//low == high 返回存放枢轴的最终位置
}

//快速排序的整体（递归）
void QuickSort(int a[], int low, int high) {
    if (low < high) {//递归跳出的条件
        //递归的一层主体
        int position = Partition(a, low, high);//找到选取基准元素的位置
        QuickSort(a, low, position - 1);//左边部分
        QuickSort(a, position + 1, high);//右边部分
    }
}