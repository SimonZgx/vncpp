//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BASEGATEWAY_H
#define MAIN_BASEGATEWAY_H

#include "curl/curl.h"
#include <string>


class BaseGateway {
private:
    BaseGateway(const BaseGateway &);

    BaseGateway &operator=(const BaseGateway &);

public:
    BaseGateway();

    virtual ~BaseGateway();
};


#endif //MAIN_BASEGATEWAY_H
