//
// Created by Simon on 2020/1/9.
//
#include "http/connection.h"

http::Connection::Connection(std::string &baseUrl) {
    this->baseUrl = baseUrl;
    std::cout << this->baseUrl << std::endl;
    this->curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

std::string &http::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

std::string &http::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); }).base(), s.end());
    return s;
}

std::string &http::trim(std::string &s) {
    return http::rtrim(http::ltrim(s));
}

size_t http::BodyCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    http::Response *r = nullptr;
    r = reinterpret_cast<http::Response *>(user_type);
    r->body.append(reinterpret_cast<char *>(contents), nmemb * size);
    return size * nmemb;
}

size_t http::HeaderCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    http::Response *r = nullptr;
    r = reinterpret_cast<http::Response *>(user_type);
    std::string header(reinterpret_cast<char *>(contents), size * nmemb);
    size_t firstOf = header.find_first_of(":");
    if (std::string::npos == firstOf) {
        trim(header);
        if (0 == header.length()) {
            return size * nmemb;
        }
        r->header[header] = "present";
    } else {
        std::string key = header.substr(0, firstOf);
        trim(key);
        std::string value = header.substr(firstOf + 1);
        trim(value);
        r->header[key] = value;
    }
    return size * nmemb;
}

void http::Connection::performCurlRequest(const char *uri, http::CallbackFunc callback) {
    http::Response ret = {};
    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode retCode = CURLE_OK;

    /** set query URL */
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    /** set callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION,
                     http::BodyCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);
    curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, http::HeaderCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, &ret);
    retCode = curl_easy_perform(this->curl);
    // free header list
    // reset curl handle
    curl_easy_reset(this->curl);
    callback(retCode, &ret);
}

void http::Connection::get(const char *url, const char *content_type, CallbackFunc callback) {
    this->performCurlRequest(url, callback);
}

void http::Connection::post(const char *url, const char *content_type, const char *data,
                            CallbackFunc callback) {
    curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, data);
    this->performCurlRequest(url, callback);
}

http::Connection::~Connection() {

}

http::Request::Request(const char *method, const char *path, const char *content_type, const http::Param &p,
                       http::CallbackFunc callback)
        : data(p), method(method), path(path), contentType(content_type), callback(callback) {

}
