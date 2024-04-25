//
// Created by GOD婴宁 on 2024/4/22.
//
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"


//定义通用函数体
void mainMenu() {
    cout << "=====================  欢迎来到客机房预约系统  ====================" << endl;
    cout << endl << "\t\t\t  请选择您的身份" << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          1.学生代表           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          2.老    师           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          3.管 理 员           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          0.退    出           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t -------------------------------\n";
    cout << "输入您的选择: ";
}

//登录函数
void loginIn(const string &fileName, int type) {
    Identity *person = nullptr;//父类指针,用于指向子类对象
    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);
    //判断文件是否存在
    if (!ifs.is_open()) {
        cout << "文件不存在或打开失败" << endl;
        ifs.close();
        return;
    }
    //准备接收用户信息
    int id = 0;
    string name;
    string pwd;
    //判断身份
    if (type == 1) {//学生
        cout << "请输入您的学号：";
        cin >> id;
    } else if (type == 2) {//老师
        cout << "请输入您的职工号：";
        cin >> id;
    }
    cout << "请输入用户名：";
    cin >> name;
    cout << "请输入密码：";
    cin >> pwd;
    //验证身份
    if (type == 1) {//学生
        int fId;//文件中的id
        string fName;//文件中的name
        string fPwd;//文件中的pwd
        while (ifs >> fId >> fName >> fPwd) {
            if (id == fId && name == fName && pwd == fPwd) {
                cout << "学生验证登录成功!" << endl;
                waitConfirm(1);
                person = new Student(id, name, pwd);
                //进入学生子菜单
                person->menu(person);
                return;
            }
        }
    } else if (type == 2) {//老师
        int fId;//文件中的id
        string fName;//文件中的name
        string fPwd;//文件中的pwd
        while (ifs >> fId >> fName >> fPwd) {
            if (id == fId && name == fName && pwd == fPwd) {
                cout << "老师验证登录成功!" << endl;
                waitConfirm(1);
                person = new Teacher(id, name, pwd);
                //进入老师子菜单
                person->menu(person);
                return;
            }
        }
    } else if (type == 3) {//管理员
        string fName;//文件中的name
        string fPwd;//文件中的pwd
        while (ifs >> fName >> fPwd) {
            if (name == fName && pwd == fPwd) {
                cout << "管理员验证登录成功!" << endl;
                waitConfirm(1);
                person = new Manager(name, pwd);
                //进入管理员子菜单
                person->menu(person);
                return;
            }
        }
    }
    cout << "验证登录失败" << endl;
    waitConfirm(1);
}

