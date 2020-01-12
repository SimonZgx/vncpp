//
// Created by Simon on 2020/1/4.
//

#include "RestClient.h"
#include <stdio.h>

restclient::Response restclient::RestClient::get(const std::string &url) {
    return Response();
}

std::string &restclient::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) {return !std::isspace(c);}));
    return s;
}

std::string &restclient::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) {return !std::isspace(c);}).base(), s.end());
    return s;
}

std::string &restclient::trim(std::string &s) {
    return rtrim(ltrim(s));
}

size_t restclient::SimpleCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
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

size_t restclient::BodyCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    restclient::Response *r = nullptr;
    r = reinterpret_cast<restclient::Response *>(user_type);
    r->body.append(reinterpret_cast<char *>(contents), nmemb * size);
    return size * nmemb;
}

size_t restclient::HeaderCallBackFunction(void *contents, size_t size, size_t nmemb, void *user_type) {
    restclient::Response *r = nullptr;
    r = reinterpret_cast<restclient::Response *>(user_type);
    std::string header(reinterpret_cast<char *>(contents), size * nmemb);
    size_t firstOf = header.find_first_of(":");
    if (std::string::npos == firstOf) {
        trim(header);
        if(0==header.length()){
            return size*nmemb;
        }
        r->header[header] = "present";
    }else{
        std::string key = header.substr(0, firstOf);
        trim(key);
        std::string value = header.substr(firstOf+1);
        trim(value);
        r->header[key] = value;
    }
    return size*nmemb;
}

