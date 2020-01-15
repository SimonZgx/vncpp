//
// Created by Simon on 2020/1/2.
//

#include <iostream>
#include <future>
#include <thread>
#include "json/json.hpp"
#include "BybitGateway.h"

using namespace std;
using json = nlohmann::json;

//void OnQuerySymbol(CURLcode retCode, const restclient::Response *res) {
//    if (retCode != CURLE_OK) {
//        cout << "Error on query symbol. Error code:" << retCode << endl;
//        return;
//    }
//    cout << "on query symbol" << endl;
//    for (auto it = res->header.begin(); it != res->header.end(); it++) {
//        cout << it->first << ":" << it->second << endl;
//    }
//    cout << res->body << endl;
//}

int main() {
//    restclient::CallbackFunc onQuerySymbol = &OnQuerySymbol;
//
    char *url = (char *) calloc(30, sizeof(char));
    strcpy(url, "https://api.bybit.com");
//    std::string baseUrl = std::string(url, std::strlen(url));
//    Http::Connection *conn = new Http::Connection(baseUrl);
//    std::thread t = std::thread(&Http::Connection::performCurlRequest,conn,"/v2/public/symbols",OnQuerySymbol);
//    t.detach();
    std::string key ="key";
    std::string secret = "secret";
    auto *client = new bybit::BybitGateway((const char*)url, key, secret);
//    client->QuerySymbols();
//    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}