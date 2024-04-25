//
// Created by GOD婴宁 on 2023/5/17.
//
//二叉树的定义及相关知识
#include <stdio.h>

//定义普通二叉树
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
//二叉树的遍历(先序遍历)
/*
void PostOrder(BiTree T){
    if(T!=NULL){
        visit(T);//访问根节点
        PostOrder(T->lchild);//递归遍历左子树
        PostOrder(T->rchild);//递归遍历右子树
    }
}
*/

//二叉树的遍历(中序遍历)
/*
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);//递归遍历左子树
        visit(T);//访问根节点
        PostOrder(T->rchild);//递归遍历右子树
    }
}
*/

//二叉树的遍历(后序遍历)
/*
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);//递归遍历左子树
        PostOrder(T->rchild);//递归遍历右子树
        visit(T);//访问根节点
    }
}
*/
//二叉树的层次遍历
/*
typedef struct LinkNode {//队列元素
    BiTNode *data;
    struct LinkNode *next;
} LinkNode;
typedef struct {
    LinkNode *front, *rear;//队头队尾
} LinkQueue;

void levelOrder(BiTree T) {
    LinkQueue Q;//1.使用辅助队列
    InitQueue(Q);//初始化队列
    BiTree p;
    EnQueue(Q);//2.根结点入队
    while (!IsEmpty(Q)) {//4.重复第三步
        DeQueue(Q, p);//3.队列不为空是，队头元素出队并访问，其左右孩子入队
        visit(p);
        if (p->lchild != NULL) {
            EnQueue(p->lchild);
        }
        if (p->rchild != NULL) {
            EnQueue(p->rchild);
        }
    }
}
*/
//线索二叉树
//对于二叉树的n+1个空链域进行线索存储

//定义线索二叉树结点
typedef struct ThreadNode {
    char data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;
//全局变量pre，指向当前访问结点的前驱结点
ThreadNode *pre;

void visit(ThreadNode *q) {
    if (q->lchild == NULL) {
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = q;
        pre->rtag = 1;
    }
    pre = q;
    printf("%c ", q->data);
}

//中序遍历二叉树，一边遍历一边线索化
void InThread(ThreadTree T) {
    if (T != NULL) {
        InThread(T->lchild);
        visit(T);
        InThread(T->rchild);
    }
}

//中序线索化二叉树T
void CreatInThread(ThreadTree T) {
    pre = NULL;
    if (T != NULL) {
        InThread(T);
        if (pre->rchild == NULL) {
            pre->rtag = 1;
        }
    }
}
//中序线索化后可以找到前驱及后驱结点
//先序线索化后可以找到后驱，采用三叉链表可以找到前驱结点
//先序线索化时要添加if(ltag==0)再递归左子树，否则进入死循环
//后序线索化后可以找到前驱，采用三叉链表可以找到后驱结点

//树和森林的存储结构
//1.双亲表示法（顺序存储），在数组存储该结点的双亲角标
//优点：对于查找双亲很方便；缺点：查找孩子需要遍历整个数组
//应用：并查集
//2.孩子表示法（顺序储存+链式存储），在数组存储所有的结点和第一孩子的结点
//优点：对于查找孩子很方便；缺点：查找双亲需要遍历整个链表
//应用：顺序服务流程（打客服电话时请你按数字号码的方式）
//3.孩子兄弟表示法：也有两个类似二叉树的指针，但所表示的含义不同，
//左指针指向第一个孩子，右指针指向兄弟
//应用：树，森林->二叉树的转换


//树的先根遍历（转换二叉树的先序遍历）、树的后跟遍历（二叉树的中序遍历）
//森林的先序遍历（转换二叉树的先序遍历）或者从左至右把树先根遍历、森林的中序遍历（二叉树的中序遍历）或者从左至右把树后根遍历

//并查集的定义、使用、优化
#define SIZE 20
int UFSets[SIZE];//集合元素数组

//初始化集合
void Initial(int S[]) {
    for (int i = 0; i < SIZE; ++i) {
        S[i] = -1;
    }
}

//Find "查"操作，找x所属集合（即返回X所属根节点）
int Find(int S[], int x) {
//    while (S[x] >= 0) {
//        x = S[x];
//    }
//    return x;
    //优化"查操作"，将查找的结点沿路的父节点全部连在根结点下
    int root =x;
    while (S[root]>=0){
        root = S[root];//找到根结点下标
    }
    while (x!=root){
        int temp =S[x];//保存当前结点的父结点
        S[x] = root;//将当前结点挂到根结点下
        x = temp;//操作当前结点的父结点到根结点下
    }
    return root;
}

//Union,"并"操作，将两个集合合并为一个(优化后：将小树并到大树)
void Union(int S[], int Root1, int Root2) {
    if (Root1 == Root2) {
        return;
    }
    if (S[Root1] < S[Root2]) {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    } else {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

//层次遍历二叉树
/*// 定义二叉树节点结构体
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 定义队列结构体
typedef struct Queue {
    TreeNode **data;
    int front;
    int rear;
    int size;
} Queue;

// 初始化队列
Queue *initQueue(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (TreeNode **)malloc(sizeof(TreeNode *) * size);
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

// 入队
void enqueue(Queue *q, TreeNode *node) {
    if (q->rear == q->size) {
        printf("Queue is full.\n");
        return;
    }
    q->data[q->rear++] = node;
}

// 出队
TreeNode *dequeue(Queue *q) {
    if (q->front == q->rear) {
        printf("Queue is empty.\n");
        return NULL;
    }
    return q->data[q->front++];
}

// 层次遍历二叉树
void levelOrder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    Queue *q = initQueue(100);
    enqueue(q, root);
    while (q->front != q->rear) {
        TreeNode *node = dequeue(q);
        printf("%d ", node->val);
        if (node->left != NULL) {
            enqueue(q, node->left);
        }
        if (node->right != NULL) {
            enqueue(q, node->right);
        }
    }
}

// 测试
int main() {
    // 构造二叉树
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->val = 3;
    root->right->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->left->val = 4;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->right->val = 5;
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    // 层次遍历二叉树
    levelOrder(root);

    return 0;
}*/



