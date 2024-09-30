//
// Created by GOD婴宁 on 2024/9/16.
//
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
using namespace std;

counting_semaphore<1> rw(1);
counting_semaphore<1> w(1);
binary_semaphore mut(1);
int value = 0;
int reader_count = 0;

void reader() {
    w.acquire();
    mut.acquire();
    if (reader_count == 0)
        rw.acquire();
    reader_count++;
    mut.release();
    w.release();
    cout << "reader: " << this_thread::get_id() << " readValue:" << value << endl;
    mut.acquire();
    --reader_count;
    if (reader_count == 0)
        rw.release();
    mut.release();
}

void writer() {
    w.acquire();
    rw.acquire();
    ++value;
    cout << "worker: " << this_thread::get_id() << " changeValue: " << value << endl;
    rw.release();
    w.release();
}


int main() {
    vector<thread> threads;
    for (int i = 0; i < 6; i++) {
        threads.emplace_back(writer);
    }
    for (int i = 0; i < 20; i++) {
        threads.emplace_back(reader);
    }
    for (auto & x: threads){
        x.join();
    }
    return 0;
}