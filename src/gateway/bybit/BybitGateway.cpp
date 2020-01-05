//
// Created by Simon on 2020/1/2.
//

#include "BybitGateway.h"
BybitGateway::BybitGateway(string baseUrl)  {
    this->restClient = new RestClient(baseUrl);
    this->Init();
}

void BybitGateway::Init() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void BybitGateway::QuerySymbols(string& path) {

}