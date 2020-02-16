//
// Created by Simon on 2020/2/9.
//

#ifndef VNCPP_WEBSOCKET_H
#define VNCPP_WEBSOCKET_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <csignal>
#include <libwebsockets.h>

using std::cout;
using std::endl;

namespace websocket{
    static int destroy_flag = 0;
    static int writeable_flag = 0;

    static inline void sigint_handler(int sig) {
        destroy_flag = 1;
    }

    class Websocket{
    public:
        Websocket(std::string& wsURL);
        ~Websocket();

        void connect();
        void onConnect();
        void send();
        void disconnect();
        void onDisconnect();
        void isConnect();
        void onMessage();
        void onFail();

        // pick the callback function to process data received from server
        int lws_event_callback(struct lws *conn, enum lws_callback_reasons reason, void *user, void *data, size_t len) {
            cout << "registering lws event callback" << endl;

            switch (reason) {
                case LWS_CALLBACK_CLIENT_ESTABLISHED: {
                    cout << "received LWS_CALLBACK_CLIENT_ESTABLISHED" << endl;
                    lws_callback_on_writable(conn);
                    break;
                }
                case LWS_CALLBACK_PROTOCOL_INIT: {
                    cout << "received LWS_CALLBACK_PROTOCOL_INIT" << endl;
                    break;
                }
                case LWS_CALLBACK_CLIENT_RECEIVE: {
                    cout << "received LWS_CALLBACK_CLIENT_RECEIVE" << endl;

                    //lwsl_debug((char *)(getJson(data).c_str()));
                    auto msg = reinterpret_cast<const char *>(data);
                    cout << msg << endl;

                    break;
                }
                case LWS_CALLBACK_CLIENT_WRITEABLE: {
                    cout << "received LWS_CALLBACK_CLIENT_WRITEABLE" << endl;

                    if (writeable_flag == 1) {
                        break;
                    }

                    writeable_flag = 1;

                    unsigned char message[512];
                    memset(&message[LWS_PRE], 0, 512 - LWS_PRE);

                    std::string json = R"({"op": "subscribe", "args": ["orderBookL2_25.BTCUSD"]})";
                    int length = json.length();
                    cout << json << endl;

                    strncpy((char *) message + LWS_PRE, json.c_str(), length);
                    lws_write(conn, &message[LWS_PRE], length, LWS_WRITE_TEXT);

                    break;
                }
                case LWS_CALLBACK_CLOSED: {
                    cout << "received LWS_CALLBACK_CLOSED" << endl;
                    break;
                }
                case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
                    cout << "received LWS_CALLBACK_CLIENT_CONNECTION_ERROR" << endl;
                    break;
                }
                default: {
                    cout << "received callback reason " << reason << endl;
                }
            }

            return 0;
        }

    private:
        std::string & wsURL;
        bool writeAble;

    };

}

#endif //VNCPP_WEBSOCKET_H
