//
// Created by Simon on 2020/1/30.
//

#include <string>
#include <iostream>
#include "wsclient.h"

void printMsg(const std::string &message){
    std::cout<<message<<std::endl;
}

int main(){
    using easywsclient::WebSocket;

    std::string testnet = "ws://stream-testnet.bybit.com/realtime";
    std::string mainnet = "ws://stream.bybit.com/realtime";

    WebSocket::pointer ws = WebSocket::from_url(testnet);
    assert(ws);

    ws->send(R"({"op":"subscribe","args":["klineV2.1.BTCUSD"]})");
    while (true) {
        ws->poll();
        ws->dispatch(printMsg);
    }

    return 0;
}
