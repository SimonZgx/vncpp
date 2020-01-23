//
// Created by Simon on 2020/1/23.
//
#include <iostream>
#include "ThreadPool.h"

using namespace std;

void displayNums(int start, int end, void (callback)(int i)) {
    for (auto i = start; i < end; i++) {
        cout << i << endl;
        this_thread::sleep_for(chrono::milliseconds (1000));
    }
    callback(end);
}

void callBack(int i){
    cout<<"Task "<<i<<" is done"<<endl;
}

int main() {
    ThreadPool pool(thread::hardware_concurrency() * 2);
    std::vector<std::future<void> > results;

    for (auto i = 0; i < 100;) {
        results.emplace_back(pool.enqueue(&displayNums, i, i + 10, callBack));
        i += 10;
    }
//    for (auto &&result: results)
//        result.get();
    this_thread::sleep_for(chrono::seconds (15));

    std::cout << std::endl;
    return 0;
}