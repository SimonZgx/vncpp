//
// Created by Simon on 2020/2/8.
//
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

enum class OrderType : unsigned int
{
    MARKET,
    LIMIT,
    STOP,
    STOP_LIMIT,
    TRAILING_STOP,
    TRAILING_STOP_LIMIT
};
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, OrderType type){
    switch (type)
    {
        case OrderType::MARKET:
            stream << "MARKET";
            break;
        case OrderType::LIMIT:
            stream << "LIMIT";
            break;
        case OrderType::STOP:
            stream << "STOP";
            break;
        case OrderType::STOP_LIMIT:
            stream << "STOP-LIMIT";
            break;
        case OrderType::TRAILING_STOP:
            stream << "TRAILING-STOP";
            break;
        case OrderType::TRAILING_STOP_LIMIT:
            stream << "TRAILING-STOP-LIMIT";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}

int main(){
    OrderType t1;
    t1 = OrderType::MARKET;
    stringstream os;
    os << t1;
    string s = os.str();
    cout<<s<<endl;
    return 0;
}