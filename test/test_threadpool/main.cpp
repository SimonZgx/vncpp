//
// Created by Simon on 2020/1/23.
//
#include <iostream>
#include "ThreadPool.h"

using namespace std;

void callBack(int i){
    cout<<"Task "<<i<<" is done"<<endl;
}

class Test{
private:
    std::shared_ptr<ThreadPool> worker;
public:
    Test(size_t size){
        this->worker = std::make_shared<ThreadPool>(size);
    }
    void displayNums(int start, int end, void (callback)(int i)) {
        for (auto i = start; i < end; i++) {
            cout << i << endl;
            this_thread::sleep_for(chrono::milliseconds (1000));
        }
        callback(end);
    }

    void addTask(int start, int end, void (callback)(int i)){
        this->worker->enqueue(&Test::displayNums, this,  start, end, callback);
    }
};

int main() {
    Test t(4);
    t.addTask(10, 20, callBack);
    cout<<"main thread"<<endl;
    cout<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    return 0;
}