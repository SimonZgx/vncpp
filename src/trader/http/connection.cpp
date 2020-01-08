//
// Created by Simon on 2020/1/9.
//
#include "http/connection.h"

restclient::Response
Http::Connection::performCurlRequest(const std::string& uri) {
    // init return type
    restclient::Response ret = {};

    std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode res = CURLE_OK;
    curl_slist* headerList = NULL;

    /** set query URL */
    curl_easy_setopt(this->curlHandle, CURLOPT_URL, url.c_str());
    /** set callback function */
    curl_easy_setopt(this->curlHandle, CURLOPT_WRITEFUNCTION,
                     Helpers::write_callback);
    /** set data object to pass to callback function */
    curl_easy_setopt(this->curlHandle, CURLOPT_WRITEDATA, &ret);
    /** set the header callback function */
    curl_easy_setopt(this->curlHandle, CURLOPT_HEADERFUNCTION,
                     Helpers::header_callback);
    /** callback object for headers */
    curl_easy_setopt(this->curlHandle, CURLOPT_HEADERDATA, &ret);
    /** set http headers */
    for (HeaderFields::const_iterator it = this->headerFields.begin();
         it != this->headerFields.end(); ++it) {
        headerString = it->first;
        headerString += ": ";
        headerString += it->second;
        headerList = curl_slist_append(headerList, headerString.c_str());
    }
    curl_easy_setopt(this->curlHandle, CURLOPT_HTTPHEADER,
                     headerList);

    // set basic auth if configured
    if (this->basicAuth.username.length() > 0) {
        std::string authString = std::string(this->basicAuth.username + ":" +
                                             this->basicAuth.password);
        curl_easy_setopt(this->curlHandle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(this->curlHandle, CURLOPT_USERPWD, authString.c_str());
    }
    /** set user agent */
    curl_easy_setopt(this->curlHandle, CURLOPT_USERAGENT,
                     this->GetUserAgent().c_str());

    // set timeout
    if (this->timeout) {
        curl_easy_setopt(this->curlHandle, CURLOPT_TIMEOUT, this->timeout);
        // dont want to get a sig alarm on timeout
        curl_easy_setopt(this->curlHandle, CURLOPT_NOSIGNAL, 1);
    }
    // set follow redirect
    if (this->followRedirects == true) {
        curl_easy_setopt(this->curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(this->curlHandle, CURLOPT_MAXREDIRS,
                         static_cast<int64_t>(this->maxRedirects));
    }

    if (this->noSignal) {
        // multi-threaded and prevent entering foreign signal handler (e.g. JNI)
        curl_easy_setopt(this->curlHandle, CURLOPT_NOSIGNAL, 1);
    }

    // if provided, supply CA path
    if (!this->caInfoFilePath.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_CAINFO,
                         this->caInfoFilePath.c_str());
    }

    // set cert file path
    if (!this->certPath.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_SSLCERT,
                         this->certPath.c_str());
    }

    // set cert type
    if (!this->certType.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_SSLCERTTYPE,
                         this->certType.c_str());
    }
    // set key file path
    if (!this->keyPath.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_SSLKEY,
                         this->keyPath.c_str());
    }
    // set key password
    if (!this->keyPassword.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_KEYPASSWD,
                         this->keyPassword.c_str());
    }

    // set web proxy address
    if (!this->uriProxy.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_PROXY,
                         uriProxy.c_str());
        curl_easy_setopt(this->curlHandle, CURLOPT_HTTPPROXYTUNNEL,
                         1L);
    }

    // set Unix socket path, if requested
    if (!this->unixSocketPath.empty()) {
        curl_easy_setopt(this->curlHandle, CURLOPT_UNIX_SOCKET_PATH,
                         this->unixSocketPath.c_str());
    }

    res = curl_easy_perform(this->curlHandle);
    if (res != CURLE_OK) {
        switch (res) {
            case CURLE_OPERATION_TIMEDOUT:
                ret.code = res;
                ret.body = "Operation Timeout.";
                break;
            case CURLE_SSL_CERTPROBLEM:
                ret.code = res;
                ret.body = curl_easy_strerror(res);
                break;
            default:
                ret.body = "Failed to query.";
                ret.code = -1;
        }
    } else {
        int64_t http_code = 0;
        curl_easy_getinfo(this->curlHandle, CURLINFO_RESPONSE_CODE, &http_code);
        ret.code = static_cast<int>(http_code);
    }

    curl_easy_getinfo(this->curlHandle, CURLINFO_TOTAL_TIME,
                      &this->lastRequest.totalTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_NAMELOOKUP_TIME,
                      &this->lastRequest.nameLookupTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_CONNECT_TIME,
                      &this->lastRequest.connectTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_APPCONNECT_TIME,
                      &this->lastRequest.appConnectTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_PRETRANSFER_TIME,
                      &this->lastRequest.preTransferTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_STARTTRANSFER_TIME,
                      &this->lastRequest.startTransferTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_REDIRECT_TIME,
                      &this->lastRequest.redirectTime);
    curl_easy_getinfo(this->curlHandle, CURLINFO_REDIRECT_COUNT,
                      &this->lastRequest.redirectCount);
    // free header list
    curl_slist_free_all(headerList);
    // reset curl handle
    curl_easy_reset(this->curlHandle);
    return ret;
}