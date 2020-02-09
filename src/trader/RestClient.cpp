//
// Created by Simon on 2020/1/4.
//

#include "RestClient.h"


//void restclient::RestClient::get(const Request &req, http::CallbackFunc callback) {
//#if __cplusplus >= 201402L
//    this->worker->enqueue(&http::Connection::get, this->conn, req.path, callback);
//    return conn->get(req.path, callback);
//#else
//    Http::Connection *conn = new Http::Connection(this->baseUrl);
//    conn->get(url, callback);
//    delete conn;
//#endif
//}


//void restclient::RestClient::post(const Request &req,
//                                  http::CallbackFunc callback) {
//#if __cplusplus >= 201402L
//    auto conn = std::make_unique<http::Connection>(this->baseUrl);
//    return conn->post(req.path, req.contentType, paramToString(req.data).c_str(), callback);
//#else
//    Http::Connection *conn = new Http::Connection(this->baseUrl);
//    conn->post(url, content_type, data, callback);
//    delete conn;
//#endif
//}
void sayHello() {
    std::cout << "hello" << std::endl;
}

void restclient::RestClient::addRequest(http::Request &req) {
    if (strcmp(req.method, "GET") == 0) {
        this->worker->enqueue(&http::Connection::get, this->conn.get(), req);
        return;
    }

    if (strcmp(req.method, "POST") == 0) {
        this->worker->enqueue(&http::Connection::post, this->conn.get(), req);
//        this->conn->post(req);
        return;
    }
}


std::string &restclient::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

std::string &restclient::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); }).base(), s.end());
    return s;
}

std::string &restclient::trim(std::string &s) {
    return rtrim(ltrim(s));
};

