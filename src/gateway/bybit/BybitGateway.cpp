//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"

shared_ptr<BybitGateway> BybitGateway::instance = nullptr;

BybitGateway::BybitGateway(const char* basePath,Setting setting) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
};

class shared_ptr<BybitGateway> BybitGateway::GetInstance(const char* basePath,Setting setting){
    if (instance == nullptr) {
        return shared_ptr<BybitGateway>(new BybitGateway(basePath,setting));
    }
    return instance;
}

void BybitGateway::QuerySymbols(const char *) {
    CURLcode res;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.bybit.com/v2/public/symbols");
        res = curl_easy_perform(curl);
        if(res!= CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}