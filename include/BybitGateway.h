//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BYBITGATEWAY_H
#define MAIN_BYBITGATEWAY_H


#include "BaseGateway.h"
#include "RestClient.h"
#include <string>
#include <map>

using namespace std;

typedef std::map<std::string, std::string> Setting;
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

    class BybitGateway : BaseGateway {
    private:
        CURL *curl;
        const char *key;
        const char *secret;
        std::string baseUrl;
        std::unique_ptr<restclient::RestClient> restClient;

    public:
        BybitGateway(const char *, Setting);

        static shared_ptr<BybitGateway> GetInstance(const char *, Setting);

        static shared_ptr<BybitGateway> instance;

        void QuerySymbols(restclient::CallbackFunc);
    };

    class RestClient : restclient::RestClient {

    };
}


#endif //MAIN_BYBITGATEWAY_H
