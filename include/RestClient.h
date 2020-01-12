//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_RESTCLIENT_H
#define MAIN_RESTCLIENT_H

#include "curl/curl.h"
#include <map>
#include <string>

namespace restclient {

    using Header = std::map<std::string, std::string>;

    typedef struct {
        void *memory;
        size_t size;
    } MemoryStruct;

    static inline std::string &ltrim(std::string &);

    static inline std::string &rtrim(std::string &);

    static inline std::string &trim(std::string &);

    size_t SimpleCallBackFunction(void *, size_t, size_t, void *);

    size_t BodyCallBackFunction(void *, size_t, size_t, void *);

    size_t HeaderCallBackFunction(void *, size_t, size_t, void *);

    typedef struct {
        int code;
        std::string body;
        Header header;
    } Response;

    using CallbackFunc = void(*)(CURLcode, const Response*);

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
