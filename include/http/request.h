//
// Created by Simon on 2020/1/23.
//

#ifndef MAIN_REQUEST_H
#define MAIN_REQUEST_H

#include <string>
#include <map>
#include "http/connection.h"

using std::string;
namespace http{

    class Request{
    public:
        string &method;
        string &path;
        string &contentType;
        Param& data;
        Request(string &, string &,string&, Param&);
    };
}

#endif //MAIN_REQUEST_H
