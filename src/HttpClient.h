#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <string>

#include "cpp-httplib/httplib.h"
#include "nlohmann/json_fwd.hpp"

#include "Endpoint/Agent.h"
#include "Endpoint/Global.h"

class HttpClient
{
    public:
        HttpClient(const std::string& bearerToken);

        void MakeRequest(const std::string& path, nlohmann::json& content);

    private:
        httplib::Client client;
};

#endif
