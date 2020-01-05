//
// Created by Simon on 2020/1/4.
//

#ifndef MAIN_RESTCLIENT_H
#define MAIN_RESTCLIENT_H

#include <iostream>
#include "curl/curl.h"
using std::string;

class RestClient {
private:
    string baseUrl;
public:
    RestClient();
    RestClient(string url){this->baseUrl = url;}
};


#endif //MAIN_RESTCLIENT_H
