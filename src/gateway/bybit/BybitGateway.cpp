//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"
#include <memory>

std::shared_ptr<bybit::BybitGateway> bybit::BybitGateway::instance = nullptr;

bybit::BybitGateway::BybitGateway(std::string &baseUrl, std::string &key, std::string &secret) :
        restClient(restclient::RestClient(baseUrl)) {
    this->baseUrl = baseUrl;
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
    http::Param p;
    http::Request req((char*)"get", (char*)"/v2/public/symbols", (char*)"", p,callback);
    this->restClient.addRequest(std::ref(req));
}

void bybit::BybitGateway::SetLeverage(int, http::CallbackFunc) {

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
