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

std::string http::HmacEncode( const char * key, const char * input) {
    const EVP_MD * engine = NULL;
    engine = EVP_sha256();

    unsigned char *p = (unsigned char*)malloc(1024);
    char buf[1024] = {0};
    char tmp[3] = {0};
    unsigned int output_length = 0;
    p = (unsigned char*)malloc(EVP_MAX_MD_SIZE);

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);
    HMAC_Update(&ctx, (unsigned char*)input, strlen(input));        // input is OK; &input is WRONG !!!

    HMAC_Final(&ctx, p, &output_length);
    HMAC_CTX_cleanup(&ctx);
    for (int i = 0; i<32; i++)
    {
        sprintf(tmp, "%02x", p[i]);
        strcat(buf, tmp);
    }
    return std::string(buf);
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

void http::Connection::performCurlRequest(http::Request& req) {
    http::Response ret = {};
//    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode retCode = CURLE_OK;

    /** set query URL */
    curl_easy_setopt(this->curl, CURLOPT_URL, req.url(this->baseUrl.c_str()));
    /** set callback function */
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION,
                     http::BodyCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &ret);
    curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, http::HeaderCallBackFunction);
    curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, &ret);
    retCode = curl_easy_perform(this->curl);
    ret.retCode = retCode;
    // free header list
    // reset curl handle
    curl_easy_reset(this->curl);
    req.callback(&ret, &req);
}

void http::Connection::get(Request& req) {
    this->performCurlRequest(req);
}

void http::Connection::post(http::Request & req) {
    std::string paramStr;
    req.toParamString(paramStr);
    std::cout<<paramStr<<std::endl;
    curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, paramStr.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, paramStr.length());
    this->performCurlRequest(req);
}

http::Connection::~Connection() {

}

http::Request::Request(const char *method, const char *path, const char *content_type,
                       http::CallbackFunc callback)
        : method(method), path(path), contentType(content_type), callback(callback) {

}

void http::Request::applySign(const char* secret) {
    timeval time;
    gettimeofday(&time, 0);
    (*this->data)["timestamp"] = std::to_string((time.tv_sec - 1) * 1000);
    std::string paramStr;
    this->toParamString(paramStr);
    (*this->data)["sign"] = HmacEncode(secret, paramStr.c_str());
}

void http::Request::toParamString(std::string &ret) {
    if ((*this->data).empty()) ret = "";
    auto pb = (*this->data).cbegin(), pe = (*this->data).cend();
    ret.append(pb->first + "=" + pb->second);
    ++pb;
    if (pe == pb)return;
    for (; pe != pb; ++pb)
        ret.append("&" + pb->first + "=" + pb->second);
}

char *http::Request::url(const char* baseUrl) {
    char* url = reinterpret_cast<char*>(calloc(strlen(baseUrl)+ strlen(this->path),sizeof(char)));
    strcat(url, baseUrl);
    strcat(url, this->path);
    return url;
}
