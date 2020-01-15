//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_RESTCLIENT_H
#define MAIN_RESTCLIENT_H

#include <map>
#include <string>
#include "curl/curl.h"
#include "http/connection.h"

namespace restclient {

    typedef struct {
        void *memory;
        size_t size;
    } MemoryStruct;

    static inline std::string &ltrim(std::string &);

    static inline std::string &rtrim(std::string &);

    static inline std::string &trim(std::string &);


    class RestClient {
    private:
        const char *baseUrl;
    public:
        void get(const std::string &url, Http::CallbackFunc);

        void post(const std::string &url,
                  const std::string &content_type,
                  const std::string &data,
                  Http::CallbackFunc);

    };


}

#endif //MAIN_RESTCLIENT_H
