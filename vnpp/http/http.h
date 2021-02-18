//
// Created by admin on 2021/2/12.
//

#ifndef VNCPP_HTTP_H
#define VNCPP_HTTP_H

#include <string>

struct HttpRequest {
    using string = std::string;

    HttpRequest();

    string uri;
    string path;

};

class HTTPClient {

public:
    HTTPClient() = default;

    void get(const std::string &url);

};

#endif //VNCPP_HTTP_H
