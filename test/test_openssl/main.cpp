//
// Created by Simon on 2020/1/27.
//

#include <iostream>
#include "openssl/sha.h"
#include "openssl/hmac.h"
using namespace std;

std::string HmacEncode( const char * key, const char * input) {
    const EVP_MD * engine = NULL;
    engine = EVP_sha256();

    auto *p = (unsigned char*)malloc(1024);
    char buf[1024] = {0};
    char tmp[3] = {0};
    unsigned int output_length = 0;
    p = (unsigned char*)malloc(EVP_MAX_MD_SIZE);

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);
    HMAC_Update(&ctx, (unsigned char*)input, strlen(input));

    HMAC_Final(&ctx, p, &output_length);
    HMAC_CTX_cleanup(&ctx);
    for (int i = 0; i<32; i++)
    {
        sprintf(tmp, "%02x", p[i]);
        strcat(buf, tmp);
    }
    return std::string(buf);
}

int main(){
    const char *secret = "t7T0YlFnYXk0Fx3JswQsDrViLg1Gh3DUU5Mr";
    const char *paramStr = "api_key=B2Rou0PLPpGqcU0Vu2&leverage=100&symbol=BTCUSD&timestamp=1542434791000";
    cout<<HmacEncode(secret, paramStr)<<endl;
}
