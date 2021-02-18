//
// Created by admin on 2021/1/16.
//

#include <httplib.h>
#include <iostream>

using namespace std;

int main() {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    httplib::SSLClient cli("api.bytick.com");
#else
    httplib::Client cli("localhost", 8080);
#endif

    if (auto res = cli.Get("/v2/public/time")) {
        cout << res->status << endl;
        cout << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    } else {
        cout << "error code: " << res.error() << std::endl;
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
        auto result = cli.get_openssl_verify_result();
        if (result) {
            cout << "verify error: " << X509_verify_cert_error_string(result) << endl;
        }
#endif
    }

    return 0;
}

