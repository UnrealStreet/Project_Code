//
// Created by GOD婴宁 on 2023/5/11.
//
//栈相关实现及操作方法
//定义链栈
#include <string.h>
#include <stdlib.h>

//定义链栈
typedef struct Stack {
    int data;
    struct Stack *next;
} LinkStack;

//使用头插法插入元素，头节点指向栈顶元素
void insertHead(LinkStack *T, int data) {
    LinkStack *temp = (LinkStack *) malloc(sizeof(LinkStack) * 1);
    temp->data = data;
    temp->next = T->next;
    T->next = temp;
}

//逆波兰表达式(后缀表达式)求值-数据栈(顺序栈)
int PolandEvaluation(char **data, int Size) {
    int temp[Size], top = 0;//top指向栈顶元素的下一个位置
    for (int i = 0; i < Size; ++i) {
        char *ch = data[i];
        if (strlen(ch) > 1 || ('0' <= ch[0] && ch[0] <= '9')) {
            temp[top++] = atoi(ch);
        } else {
            int num2 = temp[--top];//先出栈的是右操作数
            int num1 = temp[--top];//后出栈的是左操作数
            switch (*ch) {
                case '+':
                    temp[top++] = num1 + num2;
                    break;
                case '-':
                    temp[top++] = num1 - num2;
                    break;
                case '*':
                    temp[top++] = num1 * num2;
                    break;
                case '/':
                    temp[top++] = num1 / num2;
                    break;
            }
        }
    }
    return temp[top - 1];
}
