//
// Created by Simon on 2020/1/4.
//

#include "RestClient.h"
#include <stdio.h>

std::string paramToString(const http::Param& p){
    if(p.empty()) return "";
    auto pb= p.cbegin(), pe= p.cend();
    std::string data= pb-> first+ "="+ pb-> second;
    ++ pb;
    if(pb== pe) return data;
    for(; pb!= pe; ++ pb)
        data+= "&"+ pb-> first+ "="+ pb-> second;
    return data;
}

void restclient::RestClient::get(Request& req, http::CallbackFunc callback) {
#if __cplusplus >= 201402L
    auto conn = std::make_unique<http::Connection>(this->baseUrl);
    return conn->get(req.path, callback);
#else
    Http::Connection *conn = new Http::Connection(this->baseUrl);
    conn->get(url, callback);
    delete conn;
#endif
}


void restclient::RestClient::post(Request& req,
                                  http::CallbackFunc callback) {
#if __cplusplus >= 201402L
    auto conn = std::make_unique<http::Connection>(this->baseUrl);
    return conn->post(req.path, req.contentType, paramToString(req.data).c_str(), callback);
#else
    Http::Connection *conn = new Http::Connection(this->baseUrl);
    conn->post(url, content_type, data, callback);
    delete conn;
#endif
}


std::string &restclient::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

std::string &restclient::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); }).base(), s.end());
    return s;
}

std::string &restclient::trim(std::string &s) {
    return rtrim(ltrim(s));
}

size_t http::SimpleCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    size_t n = size * nmemb;
    restclient::MemoryStruct *memoryStruct = (restclient::MemoryStruct *) user_type;
    void *ptr = nullptr;
    ptr = realloc(memoryStruct->memory, memoryStruct->size + n + 1);
    if (ptr == nullptr) {
        fprintf(nullptr, "not enough memory(realloc return NULL)\n");
        return 0;
    }

    memoryStruct->memory = ptr;
    //append data
    memcpy(&(((char *) memoryStruct->memory)[memoryStruct->size]), contents, n);
    memoryStruct->size += n;
    ((char *) memoryStruct->memory)[memoryStruct->size] = '\0';
    return n;
};

