//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"

#include <memory>

std::shared_ptr<bybit::BybitGateway> bybit::BybitGateway::instance = nullptr;

bybit::BybitGateway::BybitGateway(std::string &baseUrl, std::string &key, std::string &secret){
    this->baseUrl = baseUrl;
    this->key = key;
    this->secret = secret;
    this->restClient =  restclient::RestClient();
};

std::shared_ptr<bybit::BybitGateway> bybit::BybitGateway::GetInstance(std::string& basePath, std::string&key, std::string&secret) {
    if (instance == nullptr) {
        return std::shared_ptr<BybitGateway>(new BybitGateway(basePath, key, secret));
    }
    return instance;
}



void bybit::BybitGateway::QuerySymbols(Http::CallbackFunc callback) {
    std::string url = this->baseUrl.append("/v2/public/symbols");
    std::thread th(&restclient::RestClient::get, std::ref(this->restClient),url, callback);
    th.detach();
}

void bybit::BybitGateway::SetLeverage(int, Http::CallbackFunc) {

}


void bybit::OnQuerySymbol(CURLcode httpRetCode, const Http::Response *res) {
    std::cout<<"On Query Symbol"<<std::endl;
    if (CURLE_OK != httpRetCode){
        std::cout<<"Query symbol request error. Error code : "<<httpRetCode<<std::endl;
        return;
    }
    std::cout<<res->body<<std::endl;
}

void bybit::OnSetLeverage(CURLcode httpRetCode, const Http::Response *res) {
    std::cout<<"On Set Leverage"<<std::endl;
    if (CURLE_OK != httpRetCode){
        std::cout<<"On Set Leverage request error. Error code : "<<httpRetCode<<std::endl;
        return;
    }
    std::cout<<res->body<<std::endl;
}
