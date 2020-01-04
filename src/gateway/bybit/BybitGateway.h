//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H


#include "BaseGateway.h"
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

};


#endif //MAIN_BYBITGATEWAY_H
