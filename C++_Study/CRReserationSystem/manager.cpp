//
// Created by GOD婴宁 on 2024/4/22.
//

#include "manager.h"
#include "myTool.h"

//默认构造函数
Manager::Manager() {
}

//有参构造函数
Manager::Manager(string name, string pwd) {
    //初始化管理员姓名和密码
    this->m_Name = std::move(name);
    this->m_Pwd = std::move(pwd);
    this->initVector();
    this->initComputer();
}

//菜单界面
void Manager::operMenu() {
    cout << "\n\t\t\t欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.删除账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.查看机房            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          5.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： ";
}

//菜单操作总函数
void Manager::menu(Identity *manager) {
    while (true) {
        system("cls");
        //调用管理员子菜单
        manager->operMenu();
        //将父类指针转为子类指针，调用子类中的特有接口
        Manager *man = (Manager *) manager;
        int select = readMenuSelection(5);
        switch (select) {
            case 1://添加账号
                man->addAccount();
                break;
            case 2://查看账号
                man->showAccount();
                break;
            case 3://删除账号
                man->deleteAccount();
                break;
            case 4://查看机房信息
                man->showComputer();
                break;
            case 5://清空预约记录
                man->cleanOrder();
                break;
            case 0://注销登录
                delete manager;
                cout << "注销成功！！！" << endl;
                waitConfirm();
                return;
        }
    }
}

//添加账号
void Manager::addAccount() {
    cout << "1.添加学生账号" << endl;
    cout << "2.添加老师账号" << endl;
    cout << "请选择添加账号类型：";

    string fileName;//操作文件名
    string tip;//提示id号
    string errorTip;//错误提示

    ofstream ofs;//文件操作对象
    int select = readMenuSelection(3);
    if (select == 1) {
        fileName = STUDENT_FILE;
        tip = "请输入学号：";
        errorTip = "学号重复，请重新输入!!!";
    } else {
        fileName = TEACHER_FILE;
        tip = "请输入职工号：";
        errorTip = "职工号重复，请重新输入!!!";
    }
    //利用追加的方式写文件
    ofs.open(fileName, ios::out | ios::app);
    int id;//学号或职工号
    string name;//姓名
    string pwd;//密码
    cout << tip;
    while (true) {
        cin >> id;
        if (checkRepeat(id, select)) {
            cout << errorTip << endl;
        } else {
            break;
        }
    }
    cout << "请输入姓名：";
    cin >> name;

    cout << "请输入密码：";
    cin >> pwd;
    //向文件中写入数据
    ofs << id << " " << name << " " << pwd << endl;
    cout << "添加成功！！！" << endl;
    ofs.close();
    initVector();
    waitConfirm(0);
}

//查看账号
void Manager::showAccount() {
    cout << "1.查看学生账号" << endl;
    cout << "2.查看老师账号" << endl;
    cout << "请选择查看账号类型：";
    int select = readMenuSelection(3);
    printAccount(select);
    waitConfirm();
}

//打印账号信息
void Manager::printAccount(int select) {
    if (select == 1) {
        cout << "所有学生账号信息如下：" << endl;
        cout << "学号\t\t姓名\t\t密码" << endl;
        for_each(vStu.begin(), vStu.end(), [](Student &s) {
            cout << s.stuId << "\t\t"
                 << s.m_Name << "\t\t"
                 << s.m_Pwd << endl;
        });
    } else {
        cout << "所有老师账号信息如下：" << endl;
        cout << "职工号\t\t姓名\t\t密码" << endl;
        for_each(vTea.begin(), vTea.end(), [](Teacher &t) {
            cout << t.empId << "\t\t"
                 << t.m_Name << "\t\t"
                 << t.m_Pwd << endl;
        });
    }
}


//删除账号
void Manager::deleteAccount() {
    cout << "1.删除学生账号" << endl;
    cout << "2.删除老师账号" << endl;
    cout << "请选择删除账号类型：";
    int select = readMenuSelection(3);
    printAccount(select);
    if (select == 1) {
        cout << "请输入要删除的学生学号：";
        int id = readMenuSelection(10001);
        for (auto it = vStu.begin(); it != vStu.end(); ++it) {
            if (it->stuId == id) {
                vStu.erase(it);
                cout << "删除成功！！！" << endl;
                ofstream ofs(STUDENT_FILE, ios::trunc);
                for (auto &s: vStu) {
                    ofs << s.stuId << " " << s.m_Name << " " << s.m_Pwd << endl;
                }
                ofs.close();//关闭文件
                waitConfirm();
                return;
            }
        }
        cout << "未找到该学生学号！！！" << endl;
        waitConfirm();
    } else {
        cout << "请输入要删除的老师职工号：";
        int id = readMenuSelection(10001);
        for (auto it = vTea.begin(); it != vTea.end(); ++it) {
            if (it->empId == id) {
                vTea.erase(it);
                ofstream ofs(TEACHER_FILE, ios::trunc);
                for (auto &t: vTea) {
                    ofs << t.empId << " " << t.m_Name << " " << t.m_Pwd << endl;
                }
                ofs.close();//关闭文件
                cout << "删除成功！！！" << endl;
                waitConfirm();
                return;
            }
        }
        cout << "未找到该老师职工号！！！" << endl;
        waitConfirm();
    }
}


//查看机房信息
void Manager::showComputer() {
    cout << "机房信息如下：" << endl;
    cout << "机房编号\t机房最大容量" << endl;
    for_each(vCom.begin(), vCom.end(), [](ComputerRoom &c) {
        cout << c.comId << "\t\t"
             << c.maxNum << "\t\t"
             << c.capacity << endl;
    });
    waitConfirm();
}

//清空预约记录
void Manager::cleanOrder() {
    cout << "确定清空预约记录吗？(Y/N)" << endl;
    if (readQuitConfirm() == 'Y') {
        ofstream ofs(ORDER_FILE, ios::trunc);
        ofs.close();
        cout << "清空预约记录成功！！！" << endl;
        waitConfirm();
    } else {
        cout << "取消清空预约记录！！！" << endl;
        waitConfirm();
    }
}

//初始化容器
void Manager::initVector() {
    //读取信息：学生或者老师
    ifstream ifs;
    //确保容器中没有数据
    vStu.clear();
    vTea.clear();
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在或打开失败" << endl;
        ifs.close();
        return;
    }
    Student s;
    while (ifs >> s.stuId >> s.m_Name >> s.m_Pwd) {
        vStu.push_back(s);
    }
    ifs.close();
    ifs.open(TEACHER_FILE, ios::in);
    Teacher t;
    while (ifs >> t.empId >> t.m_Name >> t.m_Pwd) {
        vTea.push_back(t);
    }
    ifs.close();
}

//初始化机房信息
void Manager::initComputer() {
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在或打开失败" << endl;
        ifs.close();
        return;
    }
    ComputerRoom com;
    while (ifs >> com.comId >> com.maxNum >> com.capacity) {
        vCom.push_back(com);
    }
    ifs.close();
}

//检测是否重复 参数1：id 参数2：类型 1表示学生 2表示老师
bool Manager::checkRepeat(int id, int type) {
    if (type == 1) {
        for (auto &s: vStu) {
            if (s.stuId == id) {
                return true;
            }
        }
    } else {
        for (auto &t: vTea) {
            if (t.empId == id) {
                return true;
            }
        }
    }
    return false;
}


