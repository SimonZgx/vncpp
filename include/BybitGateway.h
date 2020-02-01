//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H

#include <string>
#include <map>
#include <memory>
#include <thread>
#include <ctime>
#include <cstring>
#include "type/Order.h"
#include "RestClient.h"


namespace bybit {
    const std::string Side[]{
            "Buy",
            "Sell",
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

    int getCurrentTime();

    void OnResponse(void *req, void *res);

    void OnOrder(void *req, void *res);

    void OnQuerySymbol(void *req, void *res);

    void OnSetLeverage(void *req, void *res);

    class BybitGateway {
    private:
        CURL *curl;
        std::string key;
        std::string secret;
        restclient::RestClient restClient;
    public:
        BybitGateway(std::string &, std::string &, std::string &);

        static std::shared_ptr<BybitGateway> GetInstance(std::string &, std::string &, std::string &);

        static std::shared_ptr<BybitGateway> instance;

        void PlaceOrder( Order& order,http::CallbackFunc= OnOrder);

        void QuerySymbols(http::CallbackFunc= OnQuerySymbol);

        void SetLeverage(int, http::CallbackFunc= OnSetLeverage);
    };

    class BybitRestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
