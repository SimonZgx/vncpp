//
// Created by admin on 2021/2/2.
//

#include <boost/lockfree/queue.hpp>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

boost::lockfree::queue<int> queue_(1000);

void write(int i) {
    for (;;)
        queue_.push(i);
}

void read() {
    for (;;) {
        int val;
        queue_.pop(val);
        std::cout << val << endl;
    }
}

int main() {

    vector<thread> ths;
    ths.reserve(6);
    for (int i = 0; i < 3; ++i) {
        ths.emplace_back(thread([i]() -> void {
            write(i);
        }));
    }

    for (int i = 0; i < 3; ++i) {
        ths.emplace_back(thread([]() -> void {
            read();
        }));
    }

    for (auto &item : ths) {
        item.join();
    }

}