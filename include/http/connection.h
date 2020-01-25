//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_CONNECTION_H
#define MAIN_CONNECTION_H

#include <curl/curl.h>
#include <string>
#include <iostream>
#include <map>


namespace http {

    using Header = std::map<std::string, std::string>;
    using Param = std::map<std::string, std::string>;
//    typedef struct {
//        double totalTime;
//        double nameLookupTime;
//        double connectTime;
//        double appConnectTime;
//        double preTransferTime;
//        double startTransferTime;
//        double redirectTime;
//        int redirectCount;
//    } Request;

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

    class Request {
    public:
        const char *method;
        const char *path;
        const char *contentType;
        const Param &data;
        http::CallbackFunc callback;

        Request(const char *method,const char *path, const char *content_type, const Param &param, http::CallbackFunc callback);
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

        void get(const char *url, const char *contentType, CallbackFunc);

        void post(const char *url,
                  const char *content_type,
                  const char *data,
                  CallbackFunc);

        void performCurlRequest(const char *uri, CallbackFunc);
    };
}

#endif //MAIN_CONNECTION_H
