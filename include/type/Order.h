//
// Created by Simon on 2020/1/29.
//

#ifndef TEST_SINGLETON_ORDER_H
#define TEST_SINGLETON_ORDER_H

#include <string>
#include <cstring>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "http/connection.h"

struct Order {
    bool reduceOnly;
    bool closeOnTrigger;
    std::string price;
    std::string volume;
    float stopLoss;
    float trailingStop;
    float takeProfit;
    std::string symbol;
    std::string orderID;
    std::string vtOrderID;
    std::string orderType;
    std::string timestamp;
    std::string side;
    std::string timeInForce;

    void makePlaceRequest(http::CallbackFunc callbackFunc, http::Request &req) {
        req.callback = callbackFunc;
        req.path = "/v2/private/order/create";
        req.method = "POST";
        boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
        vtOrderID = boost::uuids::to_string(a_uuid);
        (*req.data)["symbol"] = symbol;
        (*req.data)["side"] = side;
        (*req.data)["order_type"] = orderType;
        (*req.data)["qty"] = volume;
        (*req.data)["price"] = price;
        (*req.data)["time_in_force"] = timeInForce;
//        (*req.data)["take_profit"] = std::to_string(takeProfit);
//        (*req.data)["stop_loss"] = std::to_string(stopLoss);
//        (*req.data)["reduce_only"] = std::to_string(reduceOnly);
//        (*req.data)["close_on_trigger"] = std::to_string(closeOnTrigger);
        (*req.data)["order_link_id"] = vtOrderID;
//        (*req.data)["trailing_stop"] = std::to_string(trailingStop);
    }

    void makeCancelRequest(http::CallbackFunc callbackFunc, http::Request &req) {
        req.callback = callbackFunc;
        req.path = "/v2/private/order/cancel";
        req.method = "POST";
        (*req.data)["symbol"] = symbol;
        (*req.data)["order_link_id"] = vtOrderID;
    }

};

#endif //TEST_SINGLETON_ORDER_H
