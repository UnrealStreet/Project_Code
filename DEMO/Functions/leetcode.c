//
// Created by GOD婴宁 on 2023/5/14.
//
//盛做多水的容器leetcode
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int maxArea(int height[], int heightSize) {
    int i = 0, j = heightSize - 1;
    int res = 0;
    int temp;
    while (i < j) {
        temp = (height[i] < height[j] ? height[i++] : height[j--]) * (j - i);
        res = res > temp ? res : temp;
    }
    return res;
}

//最小覆盖字串（哈希表+滑动窗口）
//长度最小的子数组（滑动窗口）
int minSubArrayLen(int target, int *nums, int numsSize) {
    //方法一:
    int left = 0, right = 0;
    int temp = nums[0];
    int length = numsSize + 1;
    while (right == numsSize - 1) {
        if (temp >= target) {
            length = length < right - left + 1 ? length : right - left + 1;
            temp -= nums[left++];
        } else {
            temp += nums[++right];
        }
    }
    if (length == numsSize + 1) {
        return 0;
    }
    return length;
    //方法二:
    /*int left = 0, right = 0;
    int sum = 0;
    int length = numsSize + 1;
    while (right < numsSize) {
        sum += nums[right++];
        while (sum >= target) {
            length = length < right - left ? length : right - left;
            sum -= nums[left++];
        }
    }
    return length == numsSize + 1 ? 0 : length;
    */
}

//135. 分发糖果
int candy(int *ratings, int ratingsSize) {
    int left[ratingsSize];//记录左、右规则
    for (int i = 0; i < ratingsSize; ++i) {//左循环记录糖果数
        if (i > 0 && ratings[i] > ratings[i - 1]) {//多加一个i>0使得数组第一个数默认为1
            left[i] = left[i - 1] + 1;
        } else {
            left[i] = 1;
        }
    }
    int right, ret = 0;
    for (int i = ratingsSize - 1; i >= 0; ++i) {//右循环记录糖果数，并计算总数
        if (i < ratingsSize - 1 && ratings[i] > ratings[i + 1]) {//多加第一个条件使得最后一个数默认为1
            right++;
        } else {
            right = 1;
        }
        ret += fmax(left[i], right);//比较左右数并把较大的数加入和中
    }
    return ret;
}

//224.基本计算器
int calculate(char *s) {
    int len = strlen(s);
    int stack[len], top = 0;
    int sign = 1;
    stack[top++] = sign;

    int ret = 0;
    int i = 0;
    while (i < len) {
        if (s[i] == ' ') {
            i++;
        } else if (s[i] == '+') {
            sign = stack[top - 1];
            i++;
        } else if (s[i] == '-') {
            sign = -stack[top - 1];
            i++;
        } else if (s[i] == '(') {
            stack[top++] = sign;
            i++;
        } else if (s[i] == ')') {
            top--;
            i++;
        } else {
            int num = 0;
            while (i < len && s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
                i++;
            }
            ret += sign * num;
        }
    }
    return ret;
}

//栈的压入、弹出序列
typedef struct {
    int top;
    int data[1000];
} stack;

void push(stack *s, int num) {
    s->top++;
    s->data[s->top] = num;
}

void pop(stack *s) {
    s->top--;
}

bool validateStackSequences(int *pushed, int pushedSize, int *popped, int poppedSize) {
    stack temp;
    temp.top = -1;
    int j = 0;
    for (int i = 0; i < pushedSize; ++i) {
        push(&temp, pushed[i]);
        while (temp.top != -1 && temp.data[temp.top] == popped[j]) {
            pop(&temp);
            j++;
        }
    }
    if (temp.top == -1) {
        return true;
    } else {
        return false;
    }
}

//剑指 Offer 32 - I. 从上到下打印二叉树（层序遍历）
//结点定义
/*
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
typedef struct queue {
    TreeNode *data;
    struct queue *next;
} queue;
struct queue *front, *rear;

//入队
void InQueue(TreeNode *node) {
    queue *temp = (queue *) malloc(sizeof(queue) * 1);
    front->next = temp;
    temp->data = node;
    temp->next = NULL;
    front = temp;
}

//出队
TreeNode *OutQueue() {
    queue *temp = rear->next;
    TreeNode *T;
    if (temp->next != NULL) {
        rear->next = temp->next;
        T =temp->data;
        free(temp);
        temp = NULL;
        return T;
    } else {
        T = temp->data;
        free(temp);
        rear->next = NULL;
        front = rear;
        return T;
    }
}

int *levelOrder(struct TreeNode *root, int *returnSize) {
    queue *Q;
    front = Q;
    rear = Q;
    returnSize = (int *) malloc(sizeof(int) * 1000);
    int i = 0;
    InQueue(root);
    while ( front->next != NULL) {
        struct TreeNode *temp = OutQueue();
        returnSize[i++] = OutQueue()->val;
        if (temp->left != NULL) {
            InQueue(temp->left);
        }
        if (temp->right != NULL) {
            InQueue(temp->right);
        }
    }
    return returnSize;
}*/


