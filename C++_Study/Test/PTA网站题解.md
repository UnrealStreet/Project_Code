# 网站题解
## 中国大学mooc-陈越、何钦铭-数据结构-2024夏季
### 函数题

### 编程题

#### 第六题  树的同构

~~~C++
#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
};

bool isSame(TreeNode *root1, TreeNode *root2) {
    if (!root1 || !root2)
        return root1 == root2;
    return root1->val == root2->val &&
           ((isSame(root1->left, root2->left) && isSame(root1->right, root2->right))
            || (isSame(root1->left, root2->right) && isSame(root1->right, root2->left)));
}


int load(vector<TreeNode *> &Nodes, int sum) {
    for (int i = 0; i < (int) Nodes.size(); i++) {
        cin >> Nodes[i]->val;
        char leftC, rightC;
        cin >> leftC >> rightC;
        if (leftC == '-')
            Nodes[i]->left = nullptr;
        else {
            int L = leftC - 48;
            Nodes[i]->left = Nodes[L];
            sum -= L;
        }
        if (rightC == '-')
            Nodes[i]->right = nullptr;
        else {
            int R = rightC - 48;
            Nodes[i]->right = Nodes[R];
            sum -= R;
        }
    }
    return sum;
}

int main() {
    int num = 0;
    cin >> num;
    int sum = (num - 1) * num / 2;
    //读入第一棵树的数据
    vector<TreeNode *> Nodes1;
    for (int i = 0; i < num; ++i)
        Nodes1.emplace_back(new TreeNode());
    int root1 = load(Nodes1, sum);
    //读入第二棵树的数据
    int num2 = 0;
    cin >> num2;
    if (num != num2) {
        cout << "No" << endl;
        return 0;
    }
    if (num == 0){
        cout << "Yes" << endl;
        return 0;
    }
    vector<TreeNode *> Nodes2;
    for (int i = 0; i < num2; ++i)
        Nodes2.emplace_back(new TreeNode());
    int root2 = load(Nodes2, sum);
    bool same = isSame(Nodes1[root1], Nodes2[root2]);
    cout << (same ? "Yes" : "No") << endl;
    return 0;
}
~~~

#### 第七题 List Leaves

```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
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
    if (result.empty())
        return;
    else
        cout << result[0];
    for (int i = 1; i < (int)result.size(); ++i) {
        cout << " " << result[i];
    }
}

int main() {
    int num = 0;
    cin >> num;
    int sum = (num - 1) * num / 2;
    char leftC, rightC;
    vector<TreeNode *> Nodes;
    for (int i = 0; i < num; ++i) {
        Nodes.emplace_back(new TreeNode({i}));
    }
    for (int i = 0; i < num; i++) {
        cin >> leftC >> rightC;
        if (leftC == '-')
            Nodes[i]->left = nullptr;
        else {
            int L = leftC - 48;
            Nodes[i]->left = Nodes[L];
            sum -= leftC - 48;
        }
        if (rightC == '-')
            Nodes[i]->right = nullptr;
        else {
            int R = rightC - 48;
            Nodes[i]->right = Nodes[R];
            sum -= rightC - 48;
        }
    }
    traver(Nodes[sum]);
    return 0;
}
```

#### 第八题 Tree Traversals Again

