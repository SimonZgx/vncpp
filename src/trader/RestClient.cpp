//
// Created by Simon on 2020/1/4.
//

#include "RestClient.h"
#include <stdio.h>

restclient::Response restclient::RestClient::get(const std::string &url) {
    return Response();
}

size_t restclient::SimpleCallBackFunction(char *contents, size_t size, size_t nmemb, void *user_type) {
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