//
// Created by admin on 2021/2/2.
//

#include <boost/lockfree/queue.hpp>

#include <iostream>

using namespace std;


int main() {

    boost::lockfree::queue<int> queue_(100);
    cout << queue_.is_lock_free() << endl;
}