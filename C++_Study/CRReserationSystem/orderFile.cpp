//
// Created by GOD婴宁 on 2024/4/23.
//

#include "orderFile.h"

//构造函数
OrderFile::OrderFile() {
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在或打开失败" << endl;
        ifs.close();
        return;
    }
    this->m_Size = 0;//初始化记录条数
    string date; //日期
    string interval;//时间段
    string stuId;//学生编号
    string stuName;//学生姓名
    string roomId;//机房编号
    string status;//预约状态
    map<string, string> m;
    //读取文件信息
    while (ifs >> stuId >> stuName >> date >> interval >> roomId >> status) {
        m.insert(interOrderData(date));
        m.insert(interOrderData(interval));
        m.insert(interOrderData(stuId));
        m.insert(interOrderData(stuName));
        m.insert(interOrderData(roomId));
        m.insert(interOrderData(status));
        this->m_orderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
        m.clear();
    }
    ifs.close();
}

//截取记录
pair<string, string> OrderFile::interOrderData(string &s) {
    string key;
    string value;

    int pos = (int) s.find(':');//找到“:”的位置
    if (pos != -1) {
        key = s.substr(0, pos);//截取“:”前的key
        value = s.substr(pos + 1, s.size() - pos - 1);//截取“:”后的value
        return make_pair(key, value);
    }
    return make_pair(key, value);
}

//更新预约记录
void OrderFile::updateOrder() {
    if (this->m_Size == 0)
        return;
    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; ++i) {
        ofs << "stuId:" << this->m_orderData[i]["stuId"]
            << " stuName:" << this->m_orderData[i]["stuName"]
            << " data:" << this->m_orderData[i]["data"]
            << " interval:" << this->m_orderData[i]["interval"]
            << " roomId:" << this->m_orderData[i]["roomId"]
            << " status:" << this->m_orderData[i]["status"] << endl;
    }
    ofs.close();
}

//查看所有预约
void OrderFile::showAllOrder() {
    OrderFile of;
    if (of.m_Size == 0) {
        cout << "系统中无预约记录" << endl;
        waitConfirm();
        return;
    }
    cout << "下列是所有预约记录：" << endl;
    for (int i = 0; i < of.m_Size; ++i) {
        cout << i + 1 << ".";
        cout << "学号：" << of.m_orderData[i]["stuId"] << "\t";
        cout << "姓名：" << of.m_orderData[i]["stuName"] << "\t";
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