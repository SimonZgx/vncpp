//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_RESTCLIENT_H
#define MAIN_RESTCLIENT_H

#include "curl/curl.h"
#include <map>
#include <string>

namespace restclient {

    typedef std::map<std::string, std::string> Header;

    typedef struct {
        void* memory;
        size_t size;
    }MemoryStruct;

    size_t SimpleCallBackFunction(char *, size_t, size_t, void *);

    typedef struct {
        int code;
        std::string body;
        Header header;
    } Response;

    class RestClient {
        Response get(const std::string &url);

        Response post(const std::string &url,
                      const std::string &content_type,
                      const std::string &data);

        Response put(const std::string &url,
                     const std::string &content_type,
                     const std::string &data);
    };


}

#endif //MAIN_RESTCLIENT_H
