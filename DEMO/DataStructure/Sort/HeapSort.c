//
// Created by GOD婴宁 on 2023/6/1.
//
//将以k为根的子树调整为大根堆
void HeadAdjust(int A[], int k, int len) {
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && A[i] < A[i + 1]) {
            i++;
        }
        if (A[0] >= A[i]) {
            break;
        } else {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

//建立大根堆
void BuildMaxHeap(int A[], int len) {
    for (int i = len / 2; i >0; --i) {
        HeadAdjust(A,i,len);
    }
}
//大根堆排序算法
void Heap(int A[],int len){
    
}