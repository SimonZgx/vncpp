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

void
Http::Connection::performCurlRequest(const std::string& uri, restclient::CallbackFunc callback) {
    restclient::Response ret = {};
    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode resCode = CURLE_OK;

    /** set query URL */
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    /** set callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION,
                     restclient::BodyCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);
    curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, restclient::HeaderCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, &ret);
    resCode = curl_easy_perform(this->curl);
    // free header list
    // reset curl handle
    curl_easy_reset(this->curl);
    callback(resCode, &ret);
}