#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <string>

#include "cpp-httplib/httplib.h"
#include "nlohmann/json_fwd.hpp"

namespace SpaceTraders
{
    class HttpClient
    {
        public:
            HttpClient(const std::string bearerToken);

            void MakeGlobalRequest(const std::string& path, nlohmann::json& content);
            void MakeAccountRequest(const std::string& agentToken, const std::string& path, nlohmann::json& content);

        private:
            void MakeRequest(const std::string& path, nlohmann::json& content);

        private:
            httplib::Client client;
            const std::string bearerToken;
    };
}

#endif
