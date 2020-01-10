//
// Created by Simon on 2020/1/2.
//

#include <iostream>
#include "http/connection.h"
#include "RestClient.h"

using namespace std;

size_t OnQuerySymbol(char *contents, size_t size, size_t n_mem, void *user_type) {

}

int main() {
    char *url = (char *) calloc(30, sizeof(char));
    strcpy(url, "https://api.bybit.com");

    std::string baseUrl = std::string(url, std::strlen(url));
    Http::Connection *conn = new Http::Connection(baseUrl);
    restclient::MemoryStruct res = conn->performCurlRequest("/v2/public/symbols");
    cout << (char *) res.memory << endl;
    return 0;
}