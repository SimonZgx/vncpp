//
// Created by Simon on 2020/1/5.
//

#ifndef MAIN_TEST_H
#define MAIN_TEST_H

#include "curl/curl.h"

class Test {
private:
    CURL* curl;
public:
    void SayHello();
};


#endif //MAIN_TEST_H
