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

    using CallbackFunc = void (*)(CURLcode, const Response *);

    class RestClient {
    private:
        const char *baseUrl;
    public:
        void get(const std::string &url, CallbackFunc);

        void post(const std::string &url,
                  const std::string &content_type,
                  const std::string &data,
                  CallbackFunc);

    };


}

#endif //MAIN_RESTCLIENT_H
