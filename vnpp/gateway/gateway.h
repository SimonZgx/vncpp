//
// Created by admin on 2021/2/13.
//

#ifndef VN_PP_GATEWAY_H
#define VN_PP_GATEWAY_H


#include <memory>
#include <string>
#include <event_engine/event_engine.h>

namespace gateway {

    using string = std::string;

    class Gateway {

    public:
        Gateway(event_engine::EventEngine *eventEngine, std::string &name);

        virtual void onEvent(event_engine::Event ev);

        virtual void onOrder();

        virtual void onPositionChange();

    private:

        event_engine::EventEnginePtr eventEngine_;
        std::string name_;
    };

    struct Request {
        string toString() const;

        string method;
        string path;
    };

    using GatewayPtr = std::shared_ptr<Gateway>;

    class RestClient {
    public:
        explicit RestClient(string url, Gateway *gateway);

        void requestInLoop(const Request &req);

    private:

        string url_;
        GatewayPtr gateway_;

    };

}


#endif //VN_PP_GATEWAY_H
