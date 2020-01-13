//
// Created by Simon on 2020/1/9.
//
#include "http/connection.h"

Http::Connection::Connection(const std::string &baseUrl) {
    this->baseUrl = baseUrl;
    std::cout << this->baseUrl << std::endl;
    this->curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void Http::Connection::performCurlRequest(const std::string &uri, restclient::CallbackFunc callback) {
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

void Http::Connection::get(const std::string &url,restclient::CallbackFunc callback) {
    this->performCurlRequest(url, callback);
}

void Http::Connection::post(const std::string &url, const std::string &content_type, const std::string &data,
                       restclient::CallbackFunc callback) {
    curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, data.size());
    this->performCurlRequest(url, callback);
}
