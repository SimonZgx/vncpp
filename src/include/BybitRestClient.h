//
// Created by Simon on 2020/1/4.
//

#ifndef MAIN_BYBITRESTCLIENT_H
#define MAIN_BYBITRESTCLIENT_H

#include "RestClient.h"
#include "curl/curl.h"
#include "OrderData.h"
class BybitRestClient : RestClient {
public:
    void PlaceOrder(OrderData& order);

    void QuerySymbol();

};

#endif //MAIN_BYBITRESTCLIENT_H