//
// Created by Simon on 2020/1/4.
//

#include "curl/curl.h"
#include <stdio.h>
int main(){
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.bybit.com/v2/public/symbols");
        res = curl_easy_perform(curl);
        if(res!= CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}