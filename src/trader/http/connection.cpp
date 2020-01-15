//
// Created by Simon on 2020/1/9.
//
#include "http/connection.h"

Http::Connection::Connection(std::string &baseUrl) {
    this->baseUrl = baseUrl;
    std::cout << this->baseUrl << std::endl;
    this->curl = curl_easy_init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

std::string &Http::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

std::string &Http::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); }).base(), s.end());
    return s;
}

std::string &Http::trim(std::string &s) {
    return Http::rtrim(Http::ltrim(s));
}

size_t Http::BodyCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    Http::Response *r = nullptr;
    r = reinterpret_cast<Http::Response *>(user_type);
    r->body.append(reinterpret_cast<char *>(contents), nmemb * size);
    return size * nmemb;
}

size_t Http::HeaderCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    Http::Response *r = nullptr;
    r = reinterpret_cast<Http::Response *>(user_type);
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

void Http::Connection::performCurlRequest(const std::string &uri, Http::CallbackFunc callback) {
    Http::Response ret = {};
    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode resCode = CURLE_OK;

    /** set query URL */
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    /** set callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION,
                     Http::BodyCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);
    curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, Http::HeaderCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, &ret);
    resCode = curl_easy_perform(this->curl);
    // free header list
    // reset curl handle
    curl_easy_reset(this->curl);
    callback(resCode, &ret);
}

void Http::Connection::get(const std::string &url,CallbackFunc callback) {
    this->performCurlRequest(url, callback);
}

void Http::Connection::post(const std::string &url, const std::string &content_type, const std::string &data,
                       CallbackFunc callback) {
    curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, data.size());
    this->performCurlRequest(url, callback);
}

Http::Connection::~Connection() {

}
