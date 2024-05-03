//
// Created by GOD婴宁 on 2024/4/22.
//
#include "teacher.h"

//默认构造函数
Teacher::Teacher() = default;

//有参构造函数
Teacher::Teacher(int empId, string name, string pwd) {
    this->empId = empId;
    this->m_Name = std::move(name);
    this->m_Pwd = std::move(pwd);
    this->initComputer();
}

//初始化机房信息
void Teacher::initComputer() {
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "机房文件不存在" << endl;
        ifs.close();
        return;
    }
    ComputerRoom com{};
    while (ifs >> com.comId >> com.maxNum >> com.capacity) {
        vCom.push_back(com);
    }
    ifs.close();
}

//菜单界面
void Teacher::operMenu() {
    cout << "\n\t\t\t欢迎教师：" << this->m_Name << "老师登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.查看所有预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.审核预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： ";
}

//菜单操作总函数
void Teacher::menu(Identity *teacher) {
    while (true) {
        system("cls");
        //调用教师子菜单
        teacher->operMenu();
        //将父类指针转为子类指针，调用教师类中的特有接口
        auto *tea = (Teacher *) teacher;
        int select = readMenuSelection(3);
        switch (select) {
            case 1://查看所有预约
                OrderFile::showAllOrder();
                break;
            case 2://审核预约
                tea->validOrder();
                break;
            default://注销登录0
                updateComputerNum();
                delete teacher;
                cout << "注销成功！" << endl;
                waitConfirm();
                return;
        }
    }
}

//审核预约
void Teacher::validOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "无需要审核的预约记录！" << endl;
        waitConfirm();
        return;
    }
    //循环审核预约记录
    while (true) {
        system("cls");
        this->operMenu();
        vector<int> v;
        int index = 0;
        cout << "\n待审核的预约记录如下：" << endl;
        bool flag = false;
        //显示所有预约记录
        for (int i = 0; i < of.m_Size; ++i) {
            if (of.m_orderData[i]["status"] == "1") {
                v.push_back(i);
                cout << ++index << "."
                     << "学号：" << of.m_orderData[i]["stuId"]
                     << "\t姓名：" << of.m_orderData[i]["stuName"]
                     << "\t预约日期：" << of.m_orderData[i]["data"]
                     << "\t时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")
                     << "\t机房号：" << of.m_orderData[i]["roomId"]
                     << "\t审核状态：正在审核" << endl;
                flag = true;
            }
        }
        //没有需要审核的预约记录
        if (!flag) {
            cout << "无需要审核的预约记录！" << endl;
            waitConfirm();
            return;
        }
        cout << "请选择审核的预约记录（输入0退出审核）：";
        int select = readMenuSelection(v.size() + 1);
        if (select == 0) {
            return;
        } else {
            cout << "1.通过" << endl;
            cout << "2.不通过" << endl;
            cout << "请输入审核结果：";
            int confirm = readMenuSelection(3);
            if (confirm == 1) {
                of.m_orderData[v[select - 1]]["status"] = "2";
                cout << "已同意该学生的申请！" << endl;
                if (of.m_orderData[v[select - 1]]["roomId"] == "1")
                    vCom[0].capacity--;
                else if (of.m_orderData[v[select - 1]]["roomId"] == "2")
                    vCom[1].capacity--;
                else
                    vCom[2].capacity--;
            } else {
                of.m_orderData[v[select - 1]]["status"] = "-1";
                cout << "已取消该学生的申请！" << endl;
            }
            of.updateOrder();
        }
        waitConfirm();
    }
}

//更新机房信息
void Teacher::updateComputerNum() {
    ofstream ofs;
    ofs.open(COMPUTER_FILE, ios::trunc);
    if (!ofs.is_open()) {
        cout << "机房文件打开失败" << endl;
        ofs.close();
        return;
    }
    for (auto &c: vCom) {
        ofs << c.comId << " " << c.maxNum << " " << c.capacity << endl;
    }
    ofs.close();
}