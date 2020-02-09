//
// Created by Simon on 2020/1/29.
//

#ifndef TEST_SINGLETON_ORDER_H
#define TEST_SINGLETON_ORDER_H

#include <string>
#include <cstring>
#include "http/connection.h"
#include <boost/uuid/uuid.hpp>

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
    std::string orderLinkID;

    void makePlaceRequest(http::CallbackFunc callbackFunc, http::Request &req) {
        req.callback = callbackFunc;
        req.path = "/v2/private/order/create";
        req.method = "POST";
//        orderLinkID =
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
//        (*req.data)["order_link_id"] = vtOrderID;
//        (*req.data)["trailing_stop"] = std::to_string(trailingStop);
    }

//    http::Request &makeCancelRequest() {
//
//    }

};

#endif //TEST_SINGLETON_ORDER_H
