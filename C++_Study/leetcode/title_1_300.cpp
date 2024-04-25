//
// Created by GOD婴宁 on 2024/3/9.
//
#include "L_common.h"

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*//
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *head = new ListNode(-1);//建立头指针
    ListNode *tail = head;
    int gap = 0;//保存进位
    int single;//保存个位
    int sum;
    while (l1 || l2) {
        int x = l1 != nullptr ? l1->val : 0;
        int y = l2 != nullptr ? l2->val : 0;
        sum = x + y + gap;
        single = sum % 10;//个位
        gap = (sum) / 10;//十位
//        if (!head) {//第一次初始化
//            head = tail = new ListNode(single);
//        } else {//用tail指针添加这次的个位并指向末尾
//            tail->next = new ListNode(single);
//            tail = tail->next;
//        }
        tail->next = new ListNode(single);
        tail = tail->next;
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    if (gap > 0) {//判断最后一次相加时是否刚好进位
        tail->next = new ListNode(gap);
    }
    return head->next;
}*/

/*// 6. Z 字形变换
string convert(string s, int numRows) {
    int size = s.size();
    int rows = numRows;//行数
    if (size <= rows || rows == 1)
        return s;
    //建立一个二维数组
    int cycle = size / (2 * rows - 2) + 1;//周期
    int col = cycle * (rows - 1);//列数
    vector<string> matrix(rows);//二维数组初始化为0-null
    string result;//接受结果
    for (int i = 0, x = 0; i < size; ++i) {
        matrix[x] += s[i];
        i % (2 * rows - 2) < rows - 1 ? x++ : x--;
    }
    for (string &temp: matrix) {
        result += temp;
    }
    return result;
}*/

//pow(x,y)
/*
double quickmul(double x, long long N) {
    double x_contribution = x;
    double res = 1.0;
    while (N != 0) {
        if (N % 2 == 1) {
            res *= x_contribution;
        }
        x_contribution *= x_contribution;
        N /= 2;
    }
    return res;
}

double myPow(double x, int n) {
    long long N = n;
    return N > 0 ? quickmul(x, N) : 1.0 / quickmul(x, -N);
}
*/
//盛最多水的容器
int maxArea(vector<int> &height) {
    int result = 0;
    for (int i = 0, j = height.size() - 1; i < j;) {
        int curRes = min(height[i],height[j]) * (j-i);
        result = max(result,curRes);
        if(height[i]<=height[j])
            i++;
        else
            j--;
    }
    return result;
}



















