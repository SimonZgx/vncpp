//
// Created by Simon on 2020/1/29.
//

#ifndef TEST_SINGLETON_ENUM_H
#define TEST_SINGLETON_ENUM_H

enum OrderType {
    LIMIT,
    MARKET,
    STOP,
    FAK,
    FOK
};

enum Status {
    SUBMITTING,
    NOTTRADED,
    PARTTRADED,
    ALLTRADED,
    CANCELLED,
    REJECTED,
};

enum TimeInForce {
    GoodTillCancel,
    ImmediateOrCancel,
    FillOrKill,
    PostOnly,
};


#endif //TEST_SINGLETON_ENUM_H
