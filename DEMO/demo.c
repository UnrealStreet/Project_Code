//
// Created by GOD婴宁 on 2023/4/16.
//
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
//测试数组的地址传值和指针的传值区别：数组传值与指针的意义不同；
/*int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int *b = a;
    int ** c = &b;
    int (*d) [5]= &a;
    int (*(*e)) [5]= &d;
    int (*(*(*f))) [5]= &e;
    printf("%p %p %p %p %p %p",a,b,c,d,e,f);
    return 0;
}*/

//      测试assert的用法
/*void test(int *p,int *a) {
    assert(p );
    assert(p==NULL);
}

int main() {
    int *p = NULL;
    int *a = NULL;
    test(p,a);
    return 0;
}*/

//测试结构体的默认值-一般是随机值。不完全初始化后，其他数据设置为0
/*
struct test{
    int i;
    char a;
    int c;
    int d;
    char e[10];
};

int main(){
    struct test a ={1};
    printf("%d %d %d %d",a.i,a.a,a.c,(a.e)[1]);
    printf(" %d %d ",a.i,a.a);
    return 0;
}*/

//测试枚举类的默认值
/*enum test{
    one = 1,
    two,
    three =1,
    four
//    three = 0
};
int main(){
    int num=three;
    printf("%d %d",two,four);
    return 0;
}*/
//测试结构体
/*struct test{
    int  age;
    int name[5];
};
int main(){
    char b = 10;
    int a =0;
    struct test t = {0};
    struct test *p = &t;
    printf("%p\n",t);
    printf("%p\n",p);
    printf("%p\n",&t);
    printf("%d",sizeof (struct test));
}*/
//测试\a
/*int main(){
    printf("\a");
    return 0;
}*/
/*int main(){
    char pr = fgetc(stdin);
    printf("%c\n",pr);
    pr = fgetc(stdin);
    printf("%c\n",pr);
    pr = fgetc(stdin);
    printf("%c\n",pr);
    return 0;
}*/


int main() {
    return 0;
}


