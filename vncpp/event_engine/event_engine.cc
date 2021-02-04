//
// Created by admin on 2021/1/16.
//

#include "event_engine/event_engine.h"

#include <iostream>

event_engine::EventEngine::EventEngine(size_t queueSize, size_t workerNum) : queue_(
        moodycamel::ConcurrentQueue<Event>(queueSize)) {
    for (size_t i = 0; i < workerNum; ++i) {
        worker_.emplace_back([this]() -> void {
            while (active_) {
                Event event;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    cond_.wait(lock, [&]() -> bool {
                        return !active_ && queue_.try_dequeue(event);
                    });

                    auto &handlers = handlerMap_[event.type];
                    for (auto &handler : handlers) {
                        handler->Handle(event);
                    }
                }
            }
        });
    }
}

event_engine::EventEngine::~EventEngine() {
    this->Stop();

    for (auto &th:worker_) {
        th.join();
    }

    for (auto &handlers:handlerMap_) {
        for (auto &hd:handlers.second) {
            hd->Quit();
        }
    }
}

void event_engine::EventEngine::Start() {

    for (auto &handlers:handlerMap_) {
        for (auto &hd:handlers.second) {
            hd->Init();
        }
    }

}

void event_engine::EventEngine::Stop() {
    active_ = false;
    cond_.notify_all();
}

void event_engine::EventEngine::Put(const event_engine::Event &event) {
    queue_.enqueue(event);
    cond_.notify_one();
}

void event_engine::EventEngine::RegisterHandler(EventType type, const event_engine::EventHandlerPtr &handler) {
    handlerMap_[type].emplace_back(handler);
}
