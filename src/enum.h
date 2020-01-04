//
// Created by Simon on 2020/1/3.
//

#ifndef MAIN_ENUM_H
#define MAIN_ENUM_H

#include <string>
#include<iostream>

using namespace std;

enum class Type{
    Active,
    Stop,
};

enum class Side {
    Buy,
    Sell,
};

enum class OrderType {
    Market,
    Limit,
};

enum class TimeInForce{
    GoodTillCancel,
    PostOnly,
    ImmediateOrCancel,
    FillOrKill,
};



#endif //MAIN_ENUM_H
