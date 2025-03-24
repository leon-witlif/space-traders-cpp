#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#pragma once

#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

class HttpClient
{
    public:
        HttpClient(const std::string& bearerToken);

        void MakeRequest(const std::string& path, nlohmann::json& content);

    private:
        httplib::Client client;
};

#endif
