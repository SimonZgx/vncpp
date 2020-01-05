//
// Created by Simon on 2020/1/2.
//

#include "BaseGateway.h"
BaseGateway::BaseGateway() {
    this->Init();
};

void BaseGateway::Init() {
    fprintf(nullptr, "init curl\n");
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

BaseGateway &BaseGateway::GetInstance() {
    static BaseGateway m_pInstance;
    return m_pInstance;
}

void BaseGateway::QuerySymbols(string &path) {
    fprintf(0, "QuerySymbols");
}
