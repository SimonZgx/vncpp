//
// Created by Simon on 2020/2/16.
//
#include "websocket.h"

websocket::Websocket::Websocket(std::string& url):wsURL(url),writeAble(false) {
    struct lws_protocols protocols[] =
            {
                    {
                            "example_protocol",
                            this->lws_event_callback,
                                 0,
                                    65536,
                    },
                    {NULL, NULL, 0, 0} /* terminator */
            };
}
