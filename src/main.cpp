//
// Created by Simon on 2020/1/2.
//

#include <iostream>
#include <future>
#include <thread>
#include <ctime>
#include "json/json.hpp"
#include "http/connection.h"

using namespace std;
using json = nlohmann::json;


int main() {
//    std::string baseUrl = "https://api-testnet.bybit.com";
//    std::string key = "8cxTAQ8w68MpL58rVb";
//    std::string secret = "lcpJ5I4Fabcgx7joliu8ArmpkOvO6dDwnqkq";
//    auto *client = new bybit::BybitGateway(baseUrl, key, secret);
//    client->QuerySymbols();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
    http::Request req;
    (*req.data)["api_key"] = "B2Rou0PLPpGqcU0Vu2";
    (*req.data)["timestamp"] = "1542434791000";
    req.applySign();
    return 0;
}