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

    inline void OnOrder(void *res, void *req){
        http::Request *request = nullptr;
        http::Response *response = nullptr;
        request = reinterpret_cast<http::Request *>(req);
        response = reinterpret_cast<http::Response *>(res);
        if (CURLE_OK != response->retCode) {
            std::cout << "On Order. Error code : " << response->retCode << std::endl;
        } else {

        }
        std::cout << response->body << std::endl;
    }

    inline void OnQuerySymbol(void *req, void *res);

    inline void OnSetLeverage(void *req, void *res);

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

        void PlaceOrder(Order &order, http::CallbackFunc= OnOrder);

        void QuerySymbols(http::CallbackFunc= OnQuerySymbol);

        void SetLeverage(int, http::CallbackFunc= OnSetLeverage);
    };

    class BybitRestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
