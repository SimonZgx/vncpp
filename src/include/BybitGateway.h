//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H


#include "BaseGateway.h"
#include "RestClient.h"
#include <string>

using namespace std;

namespace bybit {
    const std::string Side[]{
            "Buy",
            "Sell"
    };

    const std::string OrderType[]{
            "Market",
            "Limit",
    };

    const std::string TimeInForce[]{
            "GoodTillCancel",
            "PostOnly",
            "ImmediateOrCancel",
            "FillOrKill",
    };
}


class BybitGateway : BaseGateway {
private:
    RestClient restClient;
public:
    BybitGateway(RestClient restClient){ this->restClient=restClient;}
};


#endif //MAIN_BYBITGATEWAY_H
