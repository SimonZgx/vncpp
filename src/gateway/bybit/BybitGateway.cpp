//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"

#include <memory>

shared_ptr<bybit::BybitGateway> bybit::BybitGateway::instance = nullptr;

bybit::BybitGateway::BybitGateway(std::string &baseUrl, std::string &key, std::string &secret) {
    this->baseUrl = baseUrl;
    this->key = key;
    this->secret = secret;
    this->restClient = std::make_unique<restclient::RestClient>();
};

shared_ptr<bybit::BybitGateway> bybit::BybitGateway::GetInstance(std::string& basePath, std::string&key, std::string&secret) {
    if (instance == nullptr) {
        return shared_ptr<BybitGateway>(new BybitGateway(basePath, key, secret));
    }
    return instance;
}

void bybit::BybitGateway::QuerySymbols(Http::CallbackFunc callback) {
    std::string url = this->baseUrl.append("/v2/public/symbols");
    std::thread t = std::thread(&restclient::RestClient::get, (*this->restClient), url, callback);
//    this->restClient->get(url, callback);

}

