//
// Created by admin on 2021/1/16.
//

#ifndef VNCPP_EVENT_ENGINE_H
#define VNCPP_EVENT_ENGINE_H

#include <atomic>
#include <vector>
#include <memory>

#include <boost/lockfree/queue.hpp>

#include "const/enum.h"


namespace event_engine {
    struct Event {
        EventType type;
        std::vector<char> data;
    };

    using EventCallback = std::function<void(const Event)>;

    class EventHandler {
    public:
        virtual void Handler() = 0;
    };

    using EventHandlerPtr = std::shared_ptr<EventHandler>;

    class EventEngine {
    public:
        EventEngine();

        void Start();

        void Stop();

        void Put(Event event);

        void RegisterHandler(EventType type, EventHandlerPtr handler);

        void UnregisterHandler(EventType type, EventHandlerPtr handler);

    private:

        std::atomic_bool active_;

    };
}


#endif //VNCPP_EVENT_ENGINE_H
