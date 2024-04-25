//
// Created by GOD婴宁 on 2023/4/8.
//
//对于有序数组的二分查找法:成功返回角标，不成功返回-1；
int BinarySearch(int arr[], int target, int arrlen) {
    int left = 0;
    int right = arrlen - 1;
    int mid;
    while (left != right + 1) {//left <= right
        mid = (left + right) / 2;//向下取整
        if (arr[mid] < target) {
            left = mid + 1;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}
