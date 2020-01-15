//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_CONNECTION_H
#define MAIN_CONNECTION_H

#include <curl/curl.h>
#include <string>
#include <iostream>
#include <map>


namespace Http {

    using Header = std::map<std::string, std::string>;

    typedef struct {
        double totalTime;
        double nameLookupTime;
        double connectTime;
        double appConnectTime;
        double preTransferTime;
        double startTransferTime;
        double redirectTime;
        int redirectCount;
    } Request;

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
        Request request;

        explicit Connection(std::string &baseUrl);

        ~Connection();

        void get(const std::string &url, CallbackFunc);

        void post(const std::string &url,
                  const std::string &content_type,
                  const std::string &data,
                  CallbackFunc);

        void performCurlRequest(const std::string &uri, CallbackFunc);
    };
}

#endif //MAIN_CONNECTION_H
