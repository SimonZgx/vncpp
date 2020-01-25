//
// Created by Simon on 2020/1/25.
//

#ifndef MAIN_THREADPOOL_H
#define MAIN_THREADPOOL_H

#include <future>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>

namespace http {
    class ThreadPool {
    private:
        bool isStop;
        std::vector<std::thread> workThreads;
        std::queue<std::function<void()>> taskQueue;
        std::mutex mutex;
        std::condition_variable cond;
    public:
        explicit ThreadPool(size_t size);

        template<class F, class... Args>
        auto enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

        ~ThreadPool();

        void stop();

        void run();
    };
}

#endif //MAIN_THREADPOOL_H
