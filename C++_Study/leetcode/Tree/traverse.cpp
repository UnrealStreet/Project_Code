//
// Created by GOD婴宁 on 2024/3/13.
//
//Definition for a binary tree node.
#include "L_common.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//二叉树的前序遍历
/*vector<int> result;

vector<int> preorderTraversal(TreeNode *root) {
    traversal(root);
    return result;
}
void traversal(TreeNode *root) {
    if (root) {
        result.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}*/
//二叉树的中序遍历

void intraversal(TreeNode *root,vector<int> &result ) {
    if (root) {
        inorderTraversal(root->left);
        result.push_back(root->val);
        inorderTraversal(root->right);
    }
}

vector<int> inorderTraversal(TreeNode *root) {
    vector<int> result;
    intraversal(root,result);
    return result;
}


//二叉树的最大深度
int maxDepth(TreeNode *root) {
    if (root)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

//二叉树的最小深度
int minDepth(TreeNode *root) {
    if (root == nullptr)
        return 0;
    if (root->right == nullptr && root->left == nullptr)
        return 1;
    //此时至少有一个子树存在叶节点
    int min_Depth = INT_MAX;//保证每次能拿到当前子树的深度
    if (root->left != nullptr) {
        min_Depth = min(minDepth(root->left), min_Depth);
    }
    if (root->right != nullptr) {
        min_Depth = min(minDepth(root->right), min_Depth);
    }
    //子树的深度加上根节点
    return min_Depth + 1;
}























