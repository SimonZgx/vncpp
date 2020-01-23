//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H

#include <string>
#include <map>
#include <thread>
#include <sys/time.h>
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

    int getCurrentTime(){
        timeval time;
        gettimeofday(&time, 0);
        return time.tv_sec;
    }

    void OnQuerySymbol (CURLcode, const Http::Response *);
    void OnSetLeverage(CURLcode, const Http::Response *);

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

    class RestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
