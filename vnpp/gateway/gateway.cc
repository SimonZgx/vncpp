//
// Created by admin on 2021/2/13.
//

#include <gateway/gateway.h>

#include <utility>

using namespace event_engine;
using namespace gateway;

Gateway::Gateway(EventEngine *eventEngine, std::string &name) : eventEngine_(eventEngine), name_(name) {

}

void Gateway::onEvent(Event event) {

}

void Gateway::onOrder() {

}

void Gateway::onPositionChange() {

}

string Request::toString() const {
    return "[path:" + path + "][method:" + method + "]";
}

RestClient::RestClient(string url, Gateway *gateway) : url_(std::move(url)), gateway_(gateway) {

}

void RestClient::requestInLoop(const Request &req) {

}
