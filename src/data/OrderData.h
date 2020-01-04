//
// Created by Simon on 2020/1/2.
//

#ifndef MAIN_ORDERDATA_H
#define MAIN_ORDERDATA_H

#include <iostream>
#include <string>
#include <ostream>
#include "enum.h"

using std::string;
using std::ostream;


class OrderData {
public:
    string symbol;
    string orderID;
    Type type;
    OrderType orderType;
    Side side;

    friend ostream &operator<<(ostream &out, const OrderData &item);
};


#endif //MAIN_ORDERDATA_H
