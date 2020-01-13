//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"

shared_ptr<bybit::BybitGateway> bybit::BybitGateway::instance = nullptr;

bybit::BybitGateway::BybitGateway(const char* basePath,Setting setting) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->restClient =
    curl = curl_easy_init();
};

class shared_ptr<bybit::BybitGateway> bybit::BybitGateway::GetInstance(const char* basePath,Setting setting){
    if (instance == nullptr) {
        return shared_ptr<BybitGateway>(new BybitGateway(basePath,setting));
    }
    return instance;
}

void bybit::BybitGateway::QuerySymbols(restclient::CallbackFunc callback) {
    std::string url = this->baseUrl.append("/v2/public/symbols");
    CURLcode res;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);
        if(res!= CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void bybit::BybitGateway::QuerySymbols(const char *, ) {

}

