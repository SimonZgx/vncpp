//
// Created by Simon on 2020/1/2.
//

#include <iostream>
#include <future>
#include <thread>
#include <ctime>
#include <cstdio>
#include "json/json.hpp"
#include "BybitGateway.h"
#include "gateway/bybit/BybitGateway.cpp"
#include "type/Order.h"
using namespace std;
using json = nlohmann::json;


int main() {
    std::string baseUrl = "https://api-testnet.bybit.com";
    std::string key = "8cxTAQ8w68MpL58rVb";
    std::string secret = "lcpJ5I4Fabcgx7joliu8ArmpkOvO6dDwnqkq";
    auto *client = new bybit::BybitGateway(baseUrl, key, secret);
    Order order;
    order.side = "Buy";
    order.volume = "5";
    order.price = "10000";
    order.timeInForce = "GoodTillCancel";
    order.orderType = "Limit";
    order.symbol="BTCUSD";
//    client->QuerySymbols();
    client->PlaceOrder(order);
//    client->SetLeverage(3);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}