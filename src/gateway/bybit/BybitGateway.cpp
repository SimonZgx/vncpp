//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"
#include <memory>

std::shared_ptr<bybit::BybitGateway> bybit::BybitGateway::instance = nullptr;

int bybit::getCurrentTime() {
    timeval time;
    gettimeofday(&time, 0);
    return time.tv_sec;
}

bybit::BybitGateway::BybitGateway(std::string &baseUrl, std::string &key, std::string &secret) :
        restClient(restclient::RestClient(baseUrl)) {
    this->key = key;
    this->secret = secret;
};

std::shared_ptr<bybit::BybitGateway>
bybit::BybitGateway::GetInstance(std::string &basePath, std::string &key, std::string &secret) {
    if (instance == nullptr) {
        return std::shared_ptr<BybitGateway>(new BybitGateway(basePath, key, secret));
    }
    return instance;
}


void bybit::BybitGateway::QuerySymbols(http::CallbackFunc callback) {
    http::Request req("GET", "/v2/public/symbols", "", callback);
    this->restClient.addRequest(std::ref(req));
}

void bybit::BybitGateway::SetLeverage(int newLeverage, http::CallbackFunc callback) {
    http::Request req("POST", "/user/leverage/save", "", callback);
    req.data = new http::Param;
    (*req.data)["symbol"] = "BTCUSD";
    (*req.data)["leverage"] = std::to_string(newLeverage);
    (*req.data)["api_key"] = this->key;
    req.applySign(this->secret.c_str());
    this->restClient.addRequest(std::ref(req));
}


void bybit::OnQuerySymbol(CURLcode httpRetCode, const http::Response *res) {
    std::cout << "On Query Symbol" << std::endl;
    if (CURLE_OK != httpRetCode) {
        std::cout << "Query symbol request error. Error code : " << httpRetCode << std::endl;
        return;
    }
    std::cout << res->body << std::endl;
}

void bybit::OnSetLeverage(CURLcode httpRetCode, const http::Response *res) {
    std::cout << "On Set Leverage" << std::endl;
    if (CURLE_OK != httpRetCode) {
        std::cout << "On Set Leverage request error. Error code : " << httpRetCode << std::endl;
        return;
    }
    std::cout << res->body << std::endl;
}
