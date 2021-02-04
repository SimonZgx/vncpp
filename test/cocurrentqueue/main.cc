//
// Created by admin on 2021/2/3.
//

#include <concurrentqueue/concurrentqueue.h>


int main() {
    moodycamel::ConcurrentQueue<int> q;
    q.enqueue(25);

    int item;
    bool found = q.try_dequeue(item);
    assert(found && item == 25);
}