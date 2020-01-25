//
// Created by Simon on 2020/1/25.
//
#include "thread_pool/threadpool.h"

http::ThreadPool::ThreadPool(size_t size) : isStop(false) {
    for (auto i = 0; i < size; i++) {
        workThreads.emplace_back(
                [this] {
                    for (;;) {
                        std::function<void()> task;
                        std::unique_lock<std::mutex> lock(this->mutex);
                        this->cond.wait(lock,
                                        [this] {
                                            return this->isStop || !this->taskQueue.empty();
                                        }
                        );
                        if (this->isStop && this->taskQueue.empty()) {
                            return;
                        }
                        task = std::move(this->taskQueue.front());
                        this->taskQueue.pop();
                        task();
                    }
                }
        );
    }
}

http::ThreadPool::~ThreadPool() {
    this->stop();
    this->cond.notify_all();
    for (std::thread &worker:this->workThreads) {
        worker.join();
    }
}

void http::ThreadPool::stop() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->isStop = true;
}

void http::ThreadPool::run() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->isStop = false;
}

template<class F, class... Args>
auto http::ThreadPool::enqueue(F &&f, Args &&... args)
-> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(this->mutex);

        // don't allow enqueueing after stopping the pool
        if (this->isStop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        this->taskQueue.emplace([task]() { (*task)(); });
    }
    this->cond.notify_one();
    return res;
}