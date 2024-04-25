//
// Created by GOD婴宁 on 2024/4/10.
//
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

WorkerManger::WorkerManger() {
    this->workerNum = 0; //初始化人数
    this->workerArray = vector<worker *>(); //初始化数组
}

WorkerManger::~WorkerManger() {
    for (auto &worker: this->workerArray) {
        delete worker;
        worker = nullptr;
    }
    this->workerArray.clear();
}

void WorkerManger::show_Menu() {
    cout << "********************************************" << endl;
    cout << "*********  欢迎使用职工管理系统！ **********" << endl;
    cout << "*************  0.退出管理程序  *************" << endl;
    cout << "*************  1.增加职工信息  *************" << endl;
    cout << "*************  2.显示职工信息  *************" << endl;
    cout << "*************  3.删除离职职工  *************" << endl;
    cout << "*************  4.修改职工信息  *************" << endl;
    cout << "*************  5.查找职工信息  *************" << endl;
    cout << "*************  6.按照编号排序  *************" << endl;
    cout << "*************  7.清空所有文档  *************" << endl;
    cout << "******************************************" << endl;
    cout << endl;
    cout << "请输入您的需求：";
}

void WorkerManger::addWorker() {
    cout << "请输入添加职工数量：";
    int addNum = 0;
    cin >> addNum;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (addNum > 0 && addNum <= 10) {
        this->workerNum += addNum;
        for (int i = 0; i < addNum; ++i) {
            int id; //职工编号
            string name; //职工姓名
            int dSelect; //部门选择
            cout << "请输入第" << i + 1 << "个新职工编号：";
            cin >> id;
            if (this->isExist(id) != -1) {
                cout << "该职工编号已存在！请重新输入！" << endl;
                i--;
                continue;
            }
            cout << "请输入第" << i + 1 << "个新职工姓名：";
            cin >> name;
            cout << "\n职工岗位：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、总裁" << endl;
            cout << "请选择职工岗位：";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            dSelect = readMenuSelection(3);
            worker *worker = nullptr;
            switch (dSelect) {
                case EMPLOYEE:
                    worker = new employee(id, name, 1);
                    break;
                case MANAGER:
                    worker = new manager(id, name, 2);
                    break;
                case BOSS:
                    worker = new boss(id, name, 3);
                    break;
                default:
                    break;
            }
            this->workerArray.push_back(worker);
        }
        cout << "成功添加" << addNum << "名新职工！" << endl;
        this->save();
    } else {
        cout << "输入数据错误！（1-10）" << endl;
    }
    system("pause");
}

void WorkerManger::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (auto &worker: this->workerArray) {
        ofs << worker->id << "\t"
            << worker->name << "\t"
            << worker->deptId << endl;
    }
    ofs.close();
}

void WorkerManger:: loadFile() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在！" << endl;
        this->workerNum = 0;
        ifs.close();
        return;
    }
    int id;
    string name;
    int dId;
    int employeeNum = 0;
    while (ifs >> id >> name >> dId) {
        worker *worker = nullptr;
        employeeNum++;
        if (dId == EMPLOYEE) {
            worker = new employee(id, name, dId);
        } else if (dId == MANAGER) {
            worker = new manager(id, name, dId);
        } else {
            worker = new boss(id, name, dId);
        }
        this->workerArray.push_back(worker);
    }
    this->workerNum = employeeNum;
    ifs.close();
}

//void WorkerManger::exitSystem(){
//    exit(0);
//}

void WorkerManger::showWorker() {
    if (this->workerNum == 0) {
        cout << "文件不存在或当前记录为空！" << endl;
    } else {
        for (auto &worker: this->workerArray) {
            worker->showMessage();
        }
    }
    cout << "请按回车键以继续...";
    string message;
    getline(cin, message); //防止直接退出
}

//根据职工编号判断职工是否存在，并删除职工
void WorkerManger::deleteWorker() {
    if (this->workerNum == 0) {
        cout << "文件不存在或当前记录为空！" << endl;
    } else {
        cout << "请输入要删除的职工编号：";
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if (index != -1) {//找到职工，删除掉index位置上的职工并保存
            delete this->workerArray[index];
            this->workerArray.erase(this->workerArray.begin() + index);
            this->workerNum--;
            //保存数据
            this->save();
            cout << "删除成功！" << endl;
        } else {
            cout << "未找到该职工！" << endl;
        }
    }
    waitConfirm();
}

//判读职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManger::isExist(int id) {
    int index = -1;
    for (auto &worker: this->workerArray) {
        index++;
        if (worker->id == id) {
            return index;
        }
    }
    return -1;
}

//修改职工信息
void WorkerManger::modifyWorker() {
    if (this->workerNum == 0) {
        cout << "文件不存在或当前记录为空！" << endl;
    } else {
        cout << "请输入要修改的职工编号：";
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if (index != -1) {
            delete this->workerArray[index];
            int newId;
            string newName;
            int dSelect;
            cout << "查到ID为" << id << "号的职工，请输入修改后的新职工编号：";
            cin >> newId;
            cout << "请输入新职工姓名：";
            cin >> newName;
            cout << "\n岗位选择：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、总裁" << endl;
            cout << "请选择职工岗位：";
            cin >> dSelect;
            worker *worker = nullptr;
            switch (dSelect) {
                case EMPLOYEE:
                    worker = new employee(newId, newName, dSelect);
                    break;
                case MANAGER:
                    worker = new manager(newId, newName, dSelect);
                    break;
                case BOSS:
                    worker = new boss(newId, newName, dSelect);
                    break;
                default:
                    break;
            }
            workerArray[index] = worker;
            cout << "修改成功！" << endl;
            this->save(); //保存数据
        } else {
            cout << "未找到对应ID号的职工，请重新选择！" << endl;
        }
        waitConfirm();
    }
}

//查找职工
void WorkerManger::searchWorker() {
    if (this->workerNum == 0) {
        cout << "文件不存在或当前记录为空！" << endl;
    } else {
        cout << "请选择查找方式：" << endl;
        cout << "1、按照职工编号查找" << endl;
        cout << "2、按照职工姓名查找" << endl;
        cout << "请选择：";
        int select = 0;
        cin >> select;
        if (select == 1) {
            int id;
            cout << "请输入查找的职工编号：";
            cin >> id;
            int index = this->isExist(id);
            if (index != -1) {//找到职工
                this->workerArray[index]->showMessage();
            } else {
                cout << "未找到该职工！" << endl;
            }
        } else if (select == 2) {
            string name;
            cout << "请输入查找的职工姓名：";
            cin >> name;
            bool flag = false;
            vector<int> indexArray;
            for (int i = 0; i < this->workerNum; ++i) {
                if (this->workerArray[i]->name == name) {
                    indexArray.push_back(i);
                    flag = true;
                }
            }
            if (flag) {
                cout << "查找成功！包含该姓名的所有职工信息如下：" << endl;
                for (auto &index: indexArray) {
                    this->workerArray[index]->showMessage();
                }
            } else {
                cout << "查找失败，未找到该职工！" << endl;
            }
        } else {
            cout << "输入选项有误！" << endl;
        }
    }
    waitConfirm();
}

//按照编号排序
void WorkerManger::sortWorker() {
    if (this->workerNum == 0) {
        cout << "文件不存在或当前记录为空！" << endl;
        waitConfirm();
        return;
    } else {
        cout << "请选择排序方式：" << endl;
        cout << "1、按照职工编号升序" << endl;
        cout << "2、按照职工编号降序" << endl;
        cout << "请选择：";
        int select = 0;
        cin >> select;
        if (select == 1) {
            sort(this->workerArray.begin(), this->workerArray.end(), [](worker *w1, worker *w2) {
                return w1->id < w2->id;
            });
        } else if (select == 2) {
            sort(this->workerArray.begin(), this->workerArray.end(), [](worker *w1, worker *w2) {
                return w1->id > w2->id;
            });
        } else {
            cout << "输入选项有误！" << endl;
            waitConfirm();
            return;
        }
    }
    this->save(); //保存数据
    cout << "排序完成！排序结果如下：" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    this->showWorker();
}

//清空文件
void WorkerManger::clearFile() {
    cout << "确认清空所有数据？（Y/N）";
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || (toupper(message[0]) != 'Y' && toupper(message[0]) != 'N'))
            cout << "输入错误，请重新输入（Y/N）：";
        else
            break;
    }
    if (toupper(message[0]) == 'Y') {
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        this->workerNum = 0;
        this->~WorkerManger();
        this->workerNum = 0; //初始化人数
        cout << "清空成功！" << endl;
    } else {
        cout << "取消清空！" << endl;
    }
    cout << "请按回车键以继续...";
    getline(cin, message); //防止直接退出
}

void WorkerManger::exitSystem() {
    //1.设置绘图边界
    double a = 0.64;
    double bound = 1.3 * sqrt(a);
    //2.开始制图
    //x,y 坐标
    double step = 0.05;//步长
    for (double y = bound; y >= -bound; y -= 2*step) {
        for (double x = -bound; x <= bound; x += step) {
            double result = pow((pow(x, 2) + pow(y, 2) - a), 3) - pow(x, 2) * pow(y, 3);
            if (result <= 0)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int readMenuSelection(int choice) {
    string message;
    //进行合法性校验
    while (true) {
        getline(cin, message);
        if (message.size() != 1 || message[0] - '0' < 0 || message[0] - '0' >= choice)
            cout << "输入错误，请重新输入：";
        else
            break;
    }
    int ans = message[0] - '0';
    //输入正确
    return ans;
}

void waitConfirm() {
    cout << "请按回车键以继续...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string message;
    getline(cin, message); //防止直接退出
}