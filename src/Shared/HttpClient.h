#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <string>

#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

namespace SpaceTraders
{
    class HttpClient
    {
        public:
            HttpClient(const std::string& bearerToken);

            nlohmann::json GlobalGetRequest(const std::string& path);

            nlohmann::json AccountGetRequest(const std::string& agentToken, const std::string& path);
            nlohmann::json AccountPostRequest(const std::string& agentToken, const std::string& path, const nlohmann::json* body = nullptr);
            void AccountPatchRequest(const std::string& agentToken, const std::string& path, const nlohmann::json* body = nullptr);

        private:
            nlohmann::json GetRequest(const std::string& path);
            nlohmann::json PostRequest(const std::string& path, const nlohmann::json* body = nullptr);
            void PatchRequest(const std::string& path, const nlohmann::json* body = nullptr);

        private:
            httplib::Client m_Client;
            const std::string& m_BearerToken;
    };
}

#endif
