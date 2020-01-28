//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_CONNECTION_H
#define MAIN_CONNECTION_H

#include <curl/curl.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <map>
#include "openssl/sha.h"
#include "openssl/hmac.h"


namespace http {

    using Header = std::map<std::string, std::string>;
    using Param = std::map<std::string, std::string>;

    typedef struct {
        int code;
        std::string body;
        Header header;
    } Response;

    using CallbackFunc = void (*)(CURLcode, const Response *);

    inline std::string &ltrim(std::string &);

    inline std::string &rtrim(std::string &);

    inline std::string &trim(std::string &);

    size_t SimpleCallBackFunction(void *, size_t, size_t, void *);

    size_t BodyCallBackFunction(void *, size_t, size_t, void *);

    size_t HeaderCallBackFunction(void *, size_t, size_t, void *);

    std::string HmacEncode(const char *key, const char *input);

    class Request {
    public:
        Request(const char *method, const char *path, const char *content_type,
                CallbackFunc callback);

        Request() : data(new Param) {};

        const char *basePath;
        const char *method;
        const char *path;
        const char *contentType;

        http::CallbackFunc callback;

        //TODO track the time-consuming
        int redirectCount;
        double totalTime;
        double nameLookupTime;
        double connectTime;
        double appConnectTime;
        double preTransferTime;
        double startTransferTime;
        double redirectTime;

        Param *data;

        void applySign(const char* secret);

        char *url(const char *baseUrl);

        void toParamString(std::string &ret);
    };

    class Connection {
    private:

        CURL *curl;
        std::string baseUrl;
        Header headerFields;
        int timeout;
        bool followRedirects;
        int maxRedirects;
        bool noSignal;

    public:

        explicit Connection(std::string &baseUrl);

        ~Connection();

        void get(Request &);

        void post(Request &);

        void performCurlRequest(const char *uri, CallbackFunc);
    };
}

#endif //MAIN_CONNECTION_H
