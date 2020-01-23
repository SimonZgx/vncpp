//
// Created by Simon on 2020/1/4.
//

#include <http/request.h>

#include "http/request.h"

http::Request::Request(std::string &method, std::string &path, std::string &content_type,Param &param) :
        path(path), method(method),contentType(content_type), data(param) {
}
