//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H

#include <string>
#include <map>
#include <thread>
#include "RestClient.h"

using namespace std;

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

    class BybitGateway  {
    private:
        CURL *curl;
        std::string key;
        std::string secret;
        std::string baseUrl;
        std::unique_ptr<restclient::RestClient> restClient;
        static void OnQuerySymbol (CURLcode, const Http::Response *){
            std::cout<<"on query symbol"<<std::endl;
        }
    public:
        BybitGateway(const char *, std::string&, std::string&);

        static shared_ptr<BybitGateway> GetInstance(const char *, std::string&, std::string&);

        static shared_ptr<BybitGateway> instance;

        void QuerySymbols(Http::CallbackFunc=OnQuerySymbol);
    };

    class RestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
