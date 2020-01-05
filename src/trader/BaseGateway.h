//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_BASEGATEWAY_H
#define MAIN_BASEGATEWAY_H

#include "OrderData.h"
#include "curl/curl.h"
#include <stdio.h>
class BaseGateway {
private:
    CURL *curl;

    void PlaceOrder();

    void OnOrder();

    BaseGateway();

    BaseGateway(const BaseGateway &);

    BaseGateway &operator=(const BaseGateway &);

    void Init();

    class GC {
        ~GC() {
            if (BaseGateway::m_pInstance)
                delete (BaseGateway::m_pInstance);
        }
    };

    static GC gc;
public:
    static BaseGateway &GetInstance();
    static BaseGateway* m_pInstance;
    void QuerySymbols(string &path);

    virtual void Connect(){};

    virtual void SendOrder(){};

};

//BaseGateway* BaseGateway::m_pInstance=0;

#endif //MAIN_BASEGATEWAY_H
