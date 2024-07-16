//
// Created by GOD婴宁 on 2024/5/11.
//
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    char data;
    int left;
    int right;
};

vector<Node> T1, T2;

bool isomorphic(int root1, int root2) {
    if (root1 == -1 || root2 == -1) {
        return root1 == root2;
    }
    return (T1[root1].data == T2[root2].data) &&
           ((isomorphic(T1[root1].left, T2[root2].left) && isomorphic(T1[root1].right, T2[root2].right)) ||
            (isomorphic(T1[root1].left, T2[root2].right) && isomorphic(T1[root1].right, T2[root2].left)));
}

int main() {
    int n;
    int root1 = 0, root2 = 0;
    cin >> n;
    T1.resize(n);
    for (int i = 0; i < n; ++i) {
        char data, left, right;
        cin >> data >> left >> right;
        if(data == 'A')
            root1 = i;
        T1[i].data = data;
        T1[i].left = (left == '-' ? -1 : left - '0');
        T1[i].right = (right == '-' ? -1 : right - '0');
    }
    cin >> n;
    T2.resize(n);
    for (int i = 0; i < n; ++i) {
        char data, left, right;
        cin >> data >> left >> right;
        if(data == 'A')
            root2 = i;
        T2[i].data = data;
        T2[i].left = (left == '-' ? -1 : left - '0');
        T2[i].right = (right == '-' ? -1 : right - '0');
    }
    if (T1.empty() || T2.empty()) {
        if (T1.empty() && T2.empty())
            cout << "Yes" << endl;
        return 0;
    }
    cout << (isomorphic(root1,root2) ? "Yes" : "No") << endl;
    return 0;
}