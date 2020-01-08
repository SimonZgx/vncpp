//
// Created by Simon on 2020/1/2.
//

#include <iostream>
#include "BybitGateway.h"
#include <map>
using namespace std;

int main() {
    map<std::string, std::string> param{{"key",""}};
    shared_ptr<BybitGateway> client = BybitGateway::GetInstance("https://api.bybit.com", param);
    return 0;
}