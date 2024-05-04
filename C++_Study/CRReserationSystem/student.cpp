//
// Created by GOD婴宁 on 2024/4/22.
//
#include "student.h"
#include "myTool.h"


//默认构造函数
Student::Student() {}

//有参构造函数
Student::Student(int id, string name, string pwd) {
    this->stuId = id;
    this->m_Name = std::move(name);
    this->m_Pwd = std::move(pwd);
    this->initComputer();
}

//菜单界面
void Student::operMenu() {
    cout << "\n\t\t\t欢迎学生代表：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.申请预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.查看我的预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.查看所有预约          |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.取消预约              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： ";
}

//菜单操作总函数
void Student::menu(Identity *student) {
    while (true) {
        system("cls");
        //调用学生子菜单
        student->operMenu();
        //将父类指针转为子类指针，调用学生类中的特有接口
        auto *stu = (Student *) student;
        int select = readMenuSelection(5);
        switch (select) {
            case 1:
                stu->applyOrder();
                break;
            case 2:
                stu->showMyOrder();
                break;
            case 3:
                OrderFile::showAllOrder();
                break;
            case 4:
                stu->cancelOrder();
                break;
            default://注销登录0
                updateComputerNum();
                delete student;
                cout << "注销成功！！！" << endl;
                waitConfirm();
                return;
        }
    }
}

//初始化机房信息
void Student::initComputer() {
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


//申请预约
void Student::applyOrder() {
    cout << "机房开放时间为周一至周五（不包含今天）" << endl;
    pair<int, string> p = selectTime();//返回预约的总天数和具体时间
    //预约日期
    cout << "请选择预约时间（请输入数字）：";
    int choice = readMenuSelection(p.first + 1);
    string date;
    date = getTime(p.second, choice);
    //时间段
    int interval;
    cout << "1.上午" << endl;
    cout << "2.下午" << endl;
    cout << "请输入申请预约时间段：";
    interval = readMenuSelection(3);
    //机房编号
    int room;
    for (auto &c: vCom) {
        cout << c.comId << "号机房剩余容量：" << c.capacity << endl;
    }
    cout << "请选择机房：";
    room = readMenuSelection(4);
    //写入预约记录
    cout << "预约成功！审核中" << endl;
    ofstream ofs(ORDER_FILE, ios::app);
    ofs << "stuId:" << this->stuId << " stuName:" << this->m_Name << " data:" << date
        << " interval:" << interval << " roomId:" << room << " status:1" << endl;
    ofs.close();
    waitConfirm();
}

//查看自身预约
void Student::showMyOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "系统中无预约记录" << endl;
        waitConfirm();
        return;
    }
    bool flag = false;
    //显示预约记录
    cout << "下列是您的预约记录：" << endl;
    for (int i = 0; i < of.m_Size; ++i) {
        if (of.m_orderData[i]["stuId"] == to_string(this->stuId)) {//找到自己的预约记录
            cout << "预约日期：" << of.m_orderData[i]["data"] << "\t";
            cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "\t";
            cout << "机房：" << of.m_orderData[i]["roomId"] << "\t";
            string status = "状态：\t";
            //状态 1为审核中 2为预约成功 -1为审核未通过 0为预约取消
            if (of.m_orderData[i]["status"] == "1") {
                status += "审核中";
            } else if (of.m_orderData[i]["status"] == "2") {
                status += "预约成功";
            } else if (of.m_orderData[i]["status"] == "-1") {
                status += "预约失败,审核未通过";
            } else {
                status += "预约已取消";
            }
            cout << status << endl;
            flag = true;
        }
    }
    if (!flag) {
        cout << "无属于您的预约记录！" << endl;
        waitConfirm();
    } else {
        cout << "是否需要按照日期排序？(Y/N):";
        if (readQuitConfirm() == 'Y')
            compare(of);
        else
            return;
    }
}

//按照日期大小排序
void Student::compare(OrderFile &of) {
    vector<int> v;//存放自己的预约记录
    for (int i = 0; i < of.m_Size; ++i) {
        if (of.m_orderData[i]["stuId"] == to_string(this->stuId)) {//找到自己的预约记录
            v.push_back(i);
        }
    }
    //冒泡排序
    for (int i = 0; i < v.size() - 1; ++i) {
        for (int j = 0; j < v.size() - i - 1; ++j) {
            int date1M = stoi(of.m_orderData[v[j]]["data"].substr(0, 2));
            int date1D = stoi(of.m_orderData[v[j]]["data"].substr(4, 2));
            int date2M = stoi(of.m_orderData[v[j + 1]]["data"].substr(0, 2));
            int date2D = stoi(of.m_orderData[v[j + 1]]["data"].substr(4, 2));
            if (date1M >= date2M && date1D > date2D) {
                swap(of.m_orderData[v[j]], of.m_orderData[v[j + 1]]);
            }
        }
    }
    //打印排好序的预约
    for (int i: v) {
        cout << "预约日期：" << of.m_orderData[i]["data"] << "\t";
        cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "\t";
        cout << "机房：" << of.m_orderData[i]["roomId"] << "\t";
        string status = "状态：\t";
        //状态 1为审核中 2为预约成功 -1为审核未通过 0为预约取消
        if (of.m_orderData[i]["status"] == "1") {
            status += "审核中";
        } else if (of.m_orderData[i]["status"] == "2") {
            status += "预约成功";
        } else if (of.m_orderData[i]["status"] == "-1") {
            status += "预约失败,审核未通过";
        } else {
            status += "预约已取消";
        }
        cout << status << endl;
    }
    waitConfirm();
}

//取消预约
void Student::cancelOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "系统中无预约记录" << endl;
        waitConfirm();
        return;
    }
    cout << "下列是正在审核中或预约成功的记录，可以进行取消" << endl;
    vector<int> v;//存放可以取消的记录
    for (int i = 0; i < of.m_Size; ++i) {
        if (of.m_orderData[i]["stuId"] == to_string(this->stuId)) {//找到自己的预约记录
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {//审核中或预约成功的记录
                v.push_back(i);
                cout << v.size() << "."
                     << "预约日期：" << of.m_orderData[i]["data"] << "\t"
                     << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "\t"
                     << "机房：" << of.m_orderData[i]["roomId"] << "\t";
                string status = "状态：\t";
                //状态 1为审核中 2为预约成功 -1为审核未通过 0为预约取消
                if (of.m_orderData[i]["status"] == "1") {
                    status += "审核中";
                } else if (of.m_orderData[i]["status"] == "2") {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    cout << "请选择取消的记录（输入0返回）：";
    int select = readMenuSelection(v.size() + 1);
    if (select == 0) {
        return;
    } else {
        cout << "是否确认取消？(Y/N):";
        if (readQuitConfirm() == 'Y') {
            of.m_orderData[v[select - 1]]["status"] = "0";
            int roomId = stoi(of.m_orderData[v[select - 1]]["roomId"]);
            if (roomId == 1)
                vCom[0].capacity++;
            else if (roomId == 2)
                vCom[1].capacity++;
            else
                vCom[2].capacity++;
            of.updateOrder();
            cout << "取消成功！" << endl;
        } else {
            cout << "取消失败！" << endl;
        }
    }
    waitConfirm();
}

//修改文件中的机房数量
void Student::updateComputerNum() {
    ofstream ofs(COMPUTER_FILE, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cout << "机房文件打开失败"
             << "\n 文件未能保存，请重新操作" << endl;
        ofs.close();
        return;
    }
    for (auto &i: vCom) {
        ofs << i.comId << " " << i.maxNum << " " << i.capacity << endl;
    }
    ofs.close();
}