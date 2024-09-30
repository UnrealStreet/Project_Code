//
// Created by GOD婴宁 on 2024/7/26.
//
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
//class animal {
//public:
//
//    int test;
//
//    virtual void show() {
//        cout << "我是动物" << endl;
//    };
//};
//
//class dog : public animal {
//public:
//    using animal::show;
//    virtual void show() {
//        cout << "I'm a dog" << endl;
//    }
//
//    void test() {
//        show();
//    }
//};
//
//class Husky : public dog {
//public:
//    int age;
//    char name[18];
//
//    Husky(int a, char *b, int c) {
//    }
//
//    void show() {
//        cout << "I'm a Husky" << endl;
//    }
//};
//
//void work(animal &a) {
//    a.show();
//}


//int main(int argc,char *argv[]){
//    cout << "argc: " << argc << endl;
//    for (int i = 0; i < argc; ++i) {
//        cout << "argv[" << i << "]: " << argv[i] << endl;
//    }
//    return 0;
//}
struct Node {
    int val;
    Node *left;
    Node *right;
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

class Solution {

};

void traver(TreeNode *root) {
    queue<TreeNode *> que;
    vector<int> result;
    if (root)
        que.push(root);
    while (!que.empty()) {
        int size = que.size();
        while (size--) {
            TreeNode *node = que.front();
            que.pop();
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
            if (node->left == nullptr && node->right == nullptr)
                result.emplace_back(node->val);
        }
    }
    cout << "结果如下：" << endl;
    if (result.empty())
        return;
    else
        cout << result[0];
    for (int i = 1; i < (int)result.size(); ++i) {
        cout << " " << result[i];
    }
    cout << endl;
}

int main() {
    ifstream ifs;
    ifs.open("F:\\Project_Code\\C++_Study\\input_test.txt",ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在或打开失败" << endl;
        ifs.close();
        return 0;
    }
    int num = 0;
    ifs >> num;
    int sum = (num - 1) * num / 2;
    char leftC, rightC;
    vector<TreeNode *> Nodes;
    for (int i = 0; i < num; ++i) {
        Nodes.emplace_back(new TreeNode({i}));
    }
    for (int i = 0; i < num; i++) {
        ifs >> leftC >> rightC;
        if (leftC == '-')
            Nodes[i]->left = nullptr;
        else {
            Nodes[i]->left = Nodes[leftC-48];
            sum -= leftC - 48;
        }
        if (rightC == '-')
            Nodes[i]->right = nullptr;
        else {
            Nodes[i]->right = Nodes[rightC -48];
            sum -= rightC - 48;
        }
    }
    ifs.close();
    traver(Nodes[sum]);
    system("pause");
    return 0;
}