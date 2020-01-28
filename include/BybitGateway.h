//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H

#include <string>
#include <map>
#include <thread>
#include <ctime>
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

    void OnQuerySymbol (CURLcode, const http::Response *);
    void OnSetLeverage(CURLcode, const http::Response *);

    class BybitGateway  {
    private:
        CURL *curl;
        std::string key;
        std::string secret;
        std::string baseUrl;
        restclient::RestClient restClient;
    public:
        BybitGateway(std::string&, std::string&, std::string&);

        static std::shared_ptr<BybitGateway> GetInstance(std::string&, std::string&, std::string&);

        static std::shared_ptr<BybitGateway> instance;

        void QuerySymbols(http::CallbackFunc=OnQuerySymbol);
        void SetLeverage(int, http::CallbackFunc=OnSetLeverage);
    };

    class BybitRestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
