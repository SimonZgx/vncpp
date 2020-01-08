//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_CONNECTION_H
#define MAIN_CONNECTION_H

#include <curl/curl.h>
#include <string>
#include "RestClient.h"

using namespace restclient;
namespace Http{

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
        Header headers;
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

    class Connection{
    public:
        Request request;

        explicit Connection(const std::string& baseUrl);
        ~Connection();

        // Instance configuration methods
        // configure basic auth
        void SetBasicAuth(const std::string& username,
                          const std::string& password);

        // set connection timeout to seconds
        void SetTimeout(int seconds);

        // set to not use signals
        void SetNoSignal(bool no);

        // set whether to follow redirects, maxRedirects indicitng the maximum
        // number of redirects to follow
        void FollowRedirects(bool follow, int maxRedirects = -1l);

        // set custom user agent
        // (this will result in the UA "foo/cool restclient-cpp/VERSION")
        void SetUserAgent(const std::string& userAgent);

        // set the Certificate Authority (CA) Info which is the path to file holding
        // certificates to be used to verify peers. See CURLOPT_CAINFO
        void SetCAInfoFilePath(const std::string& caInfoFilePath);

        // set CURLOPT_SSLCERT
        void SetCertPath(const std::string& cert);

        // set CURLOPT_SSLCERTTYPE
        void SetCertType(const std::string& type);

        // set CURLOPT_SSLKEY. Default format is PEM
        void SetKeyPath(const std::string& keyPath);

        // set CURLOPT_KEYPASSWD.
        void SetKeyPassword(const std::string& keyPassword);

        // set CURLOPT_PROXY
        void SetProxy(const std::string& uriProxy);

        // set CURLOPT_UNIX_SOCKET_PATH
        void SetUnixSocketPath(const std::string& unixSocketPath);

        std::string GetUserAgent();

        RestClient::Connection::Info GetInfo();

        // set headers
        void SetHeaders(RestClient::HeaderFields headers);

        // get headers
        RestClient::HeaderFields GetHeaders();

        // append additional headers
        void AppendHeader(const std::string& key,
                          const std::string& value);


        // Basic HTTP verb methods
        Response get(const std::string& uri);
        Response post(const std::string& uri,
                                  const std::string& data);
        Response put(const std::string& uri,
                                 const std::string& data);
        Response patch(const std::string& uri,
                                   const std::string& data);
        Response del(const std::string& uri);
        Response head(const std::string& uri);
        Response options(const std::string& uri);
    };
}

#endif //MAIN_CONNECTION_H
