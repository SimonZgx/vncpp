//
// Created by Simon on 2020/1/9.
//
#include "http/connection.h"

Http::Connection::Connection(const std::string& baseUrl){
    this->baseUrl = baseUrl;
    std::cout<<this->baseUrl<<std::endl;
    this->curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

restclient::MemoryStruct
Http::Connection::performCurlRequest(const std::string& uri, size_t callBack(char *, size_t , size_t, void *)) {
    restclient::MemoryStruct ret = {};
    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode res = CURLE_OK;

    /** set query URL */
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    /** set callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION,
                     callBack);
    /** set data object to pass to callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);


    res = curl_easy_perform(this->curl);
    // free header list
    // reset curl handle
    curl_easy_reset(this->curl);
    return ret;
}