//
// Created by GOD婴宁 on 2024/9/16.
//

#include <iostream>
#include <future>
#include <thread>
#include <functional>

using namespace std;
//async的简单使用
# if 0
int main() {
    future<int> value = async(launch::async,[](int x){
        cout << this_thread::get_id() << endl;
        return x+100;
    },100);
    cout << this_thread::get_id() << endl;
    cout<< value.get();
    return 0;
}
#endif
//promise的简单使用
# if 0
int main(){
    promise<int> p;
    thread t1([](promise<int> &p){
        p.set_value_at_thread_exit(100);
        cout << "sleep" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "wake up" << endl;
    }, ref(p));
    future<int> f = p.get_future();
    cout << f.get() << endl;
    t1.join();
    return 0;
}
#endif
//packaged_task的简单使用
int main(){
    function<int(int)> func = [](int x){
        cout << this_thread::get_id() << endl;
        return x+100;
    };
    packaged_task<int(int)> task(func);
    thread t1(ref(task),1 00);
    future<int> f = task.get_future();
    cout << f.get() << endl;
    cout << "main thread id: " << this_thread::get_id() << endl;
    t1.join();
    return 0;
}