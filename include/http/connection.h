//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_CONNECTION_H
#define MAIN_CONNECTION_H

#include <curl/curl.h>
#include <string>
#include <iostream>
#include "RestClient.h"

namespace Http {

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
        std::string baseUrl;
        restclient::Header headers;
        int timeout;
        bool followRedirects;
        int maxRedirects;
        bool noSignal;
        struct {
            std::string username;
            std::string password;
        } basicAuth;

        std::string certPath;
        std::string certType;
        std::string keyPath;
        std::string keyPassword;
        std::string customUserAgent;
        std::string uriProxy;
        std::string unixSocketPath;
        Request lastRequest;
    } Config;

    class Connection {
    private:

        CURL *curl;
        std::string baseUrl;
        restclient::Header headerFields;
        int timeout;
        bool followRedirects;
        int maxRedirects;
        bool noSignal;
    public:
        Request request;

        explicit Connection(const std::string &baseUrl);

        ~Connection();

        void get(const std::string &url, restclient::CallbackFunc);

        void post(const std::string &url,
                  const std::string &content_type,
                  const std::string &data,
                  restclient::CallbackFunc);

        void performCurlRequest(const std::string &uri, restclient::CallbackFunc);
    };
}

#endif //MAIN_CONNECTION_H
