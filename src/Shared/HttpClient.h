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

            void GlobalGetRequest(const std::string& path, nlohmann::json& content);

            void AccountGetRequest(const std::string& agentToken, const std::string& path, nlohmann::json& content);
            void AccountPostRequest(const std::string& agentToken, const std::string& path);
            void AccountPatchRequest(const std::string& agentToken, const std::string& path, const nlohmann::json& json);

        private:
            void GetRequest(const std::string& path, nlohmann::json& content);
            void PostRequest(const std::string& path);
            void PatchRequest(const std::string& path, const nlohmann::json& json);

        private:
            httplib::Client m_Client;
            const std::string& m_BearerToken;
    };
}

#endif
