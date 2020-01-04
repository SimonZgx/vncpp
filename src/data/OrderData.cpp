//
// Created by Simon on 2020/1/2.
//

#include "OrderData.h"

ostream &operator<<(ostream &out, const OrderData &item) {
    out<<item.OrderID<<" "<<item.Symbol;
    return out;
}
