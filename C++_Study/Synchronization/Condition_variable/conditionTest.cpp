//
// Created by GOD婴宁 on 2024/9/13.
//
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <atomic>
using namespace std;

/*
 * 两个线程交替打印奇偶数
 *
mutex mtx;
condition_variable cv;
int myValue = 0;
bool flag = false;

void increase(int threadId) {
    for (int i = 0; i < 10; i++) {
        unique_lock<mutex> unLock(mtx);
        cv.wait(unLock, [&] { return threadId == 1 ? !flag : flag; });
        ++myValue;
        cout << "ThreadID: " << threadId << " myValue:" << myValue << endl;
        flag = !flag;
        cv.notify_one();
    }
}

int main() {
    thread t1(increase, 1);
    thread t2(increase, 2);
    t1.join();
    t2.join();
    return 0;
}*/
/*
int shareData = 0;
shared_mutex rw_mutex;

void reader() {
    shared_lock<shared_mutex> rMutex(rw_mutex);
    cout << "reader: " << this_thread::get_id() << " Data: " << shareData << endl;
}

void writer() {
    unique_lock<shared_mutex> wMutex(rw_mutex);
    ++shareData;
    cout << "writer: " << shareData << endl;
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < 50; i++) {
        threads.emplace_back(reader);
    }
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(writer);
    }
    for (auto &x: threads) {
        x.join();
    }
    return 0;
}
*/

int main() {

    return 0;
}