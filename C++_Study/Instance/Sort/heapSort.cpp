//
// Created by GOD婴宁 on 2024/8/17.
//
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void heapAdjust(vector<int> &v, int cur, int len) {
    v[0] = v[cur];
    for (int i = 2 * cur; i <= len; i *= 2) {
        if (i < len && v[i] > v[i + 1])
            i++;
        if (v[0] <= v[i])
            break;
        else {
            v[cur] = v[i];
            cur = i;
        }
    }
    v[cur] = v[0];
}

void buildHeap(vector<int> &v, int len) {
    for (int i = len / 2; i > 0; i--) {
        heapAdjust(v, i, len);
    }
}

void heapSort(vector<int> &v, int len) {
    buildHeap(v, len);
    for (int i = len; i > 1; i--) {
        swap(v[1], v[i]);
        heapAdjust(v, 1, i - 1);
    }
}

void heapDelete(vector<int> &v, int target) {
    int len = (int) v.size() - 1;
    swap(v[target], v[len]);
    v.pop_back();
    heapAdjust(v, target, len - 1);
}

void heapInsert(vector<int> &v, int target) {
    v.push_back(target);
    int len = (int) v.size() - 1;
    int temp = len;
    for (int i = len / 2; i > 0; i /= 2) {
        if (v[i] > target) {
            swap(v[i], v[temp]);
            temp = i;
        } else
            break;
    }
}

void printHeap(vector<int> &v) {
    for (int i = 1; i < (int) v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;
}

void isHeap(const vector<int> &v) {
    for (int i = 1; i <= ((int) v.size() - 1) / 2; ++i) {
        int left = 2 * i;
        if (left < (int) v.size() - 1 && v[left] > v[left + 1])
            left++;
        if (v[i] > v[left]) {
            cout << "Not a heap" << endl;
            return;
        }
    }
    cout << "Is a heap" << endl;
}

int main() {
    //测试堆排序
    srand(time(0));
    int nums = 10;
    vector<int> sample(nums + 1, 0);
    for (int i = 1; i <= nums; i++) {
        sample[i] = (rand() % 100);
    }
    printHeap(sample);
    heapSort(sample, nums);
    printHeap(sample);
      //测试在堆中删除和插入
    /*buildHeap(sample, nums);
    printHeap(sample);
    isHeap(sample);
    cout << "delete the 5th element:" << sample[5] << endl;
    heapDelete(sample, 5);
    printHeap(sample);
    isHeap(sample);
    heapInsert(sample, 5);
    printHeap(sample);
    isHeap(sample);*/
    system("pause");
    return 0;
}