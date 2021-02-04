//
// Created by admin on 2021/1/16.
//

#ifndef VNCPP_EVENT_ENGINE_H
#define VNCPP_EVENT_ENGINE_H

#include <atomic>
#include <vector>
#include <memory>
#include <unordered_map>
#include <concurrentqueue/concurrentqueue.h>

#include "const/enum.h"


namespace event_engine {
    struct Event {
        EventType type;
        std::vector<char> data;
    };

    using EventCallback = std::function<void(const Event)>;

    class EventHandler {
    public:
        virtual void Init() = 0;

        virtual void Handle(const Event &event) = 0;

        virtual void Quit() = 0;
    };

    using EventHandlerPtr = std::shared_ptr<EventHandler>;


    class EventEngine {
    public:
        EventEngine(size_t queueSize, size_t workerNum);

        ~EventEngine();

        void Start();

        void Stop();

        void Put(const Event &event);

        void RegisterHandler(EventType type, const EventHandlerPtr &handler);

    private:
        std::mutex mutex_;
        std::condition_variable cond_;
        std::unordered_map<EventType, std::vector<EventHandlerPtr>> handlerMap_;
        std::atomic_bool active_{};
        std::vector<std::thread> worker_;
        moodycamel::ConcurrentQueue<Event> queue_;

        void Process();
    };
}


#endif //VNCPP_EVENT_ENGINE_H
