//
// Created by Simon on 2020/1/8.
//

#ifndef MAIN_RESTCLIENT_H
#define MAIN_RESTCLIENT_H

#include <map>
#include <string>
#include <future>
#include "curl/curl.h"
#include "http/connection.h"
#include "http/request.h"

using http::Request;

namespace restclient {

    typedef struct {
        void *memory;
        size_t size;
    } MemoryStruct;

    static inline std::string &ltrim(std::string &);

    static inline std::string &rtrim(std::string &);

    static inline std::string &trim(std::string &);


    class RestClient {
    private:
        std::unique_ptr<http::Connection> conn;
        std::string baseUrl;
    public:

        RestClient(std::string &baseUrl) {
            this->conn = std::make_unique<http::Connection>(baseUrl);
        }

        void get(Request &, http::CallbackFunc);

        void post(Request &,
                  http::CallbackFunc);

    };

    class ThreadPool {
        ThreadPool(size_t);

        template<class F, class...Args>
        auto enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;
    };


}

#endif //MAIN_RESTCLIENT_H
