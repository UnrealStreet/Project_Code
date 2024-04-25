//
// Created by GOD婴宁 on 2024/3/4.
//
//快速排序
/*int Partition(int (&arr)[], int start, int end) {
    int pivot = arr[start];
    while (start < end) {
        while (arr[end] >= pivot && start < end)
            end--;
        arr[start] = arr[end];
        while (arr[start] <= pivot && start < end)
            start++;
        arr[start] = arr[end];
    }
    arr[start] = pivot;
    return start;
}

void quicksort(int (&arr)[], int start, int end) {
    if (start < end) {
        int pivotpos = Partition(arr, start, end);
        quicksort(arr, start, pivotpos - 1);
        quicksort(arr, pivotpos + 1, end);
    }
}*/
//采用随机索引
class Solution {
    int Partition(vector<int>& arr, int start, int end) {

        swap(arr[start],arr[start+rand() % (end - start)]);// 随机索引
        int pivot = arr[start];
        while (start < end) {
            while (arr[end] >= pivot && start < end)
                end--;
            arr[start] = arr[end];
            while (arr[start] <= pivot && start < end)
                start++;
            arr[end] = arr[start];
        }
        arr[start] = pivot;
        return start;
    }

    void quicksort(vector<int>& arr, int start, int end) {
        if (start < end) {
            int pivotpos = Partition(arr, start, end);
            quicksort(arr, start, pivotpos - 1);
            quicksort(arr, pivotpos + 1, end);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums, 0, (int)nums.size() - 1);

        return nums;
    }
};