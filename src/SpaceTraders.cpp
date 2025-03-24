#include <iostream>
#include <optional>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace SpaceTraders
{
    namespace Model
    {
        namespace Agent
        {
            struct Agent
            {
                std::optional<std::string> accountId;
            };

            void from_json(const json& json, Agent& agent)
            {
                json.contains("accountId") ? agent.accountId = json.at("accountId").get<std::string>() : agent.accountId = std::nullopt;
            }
        }
    }

    namespace Endpoint
    {
        namespace Agent
        {
            struct ListAgents
            {
                std::vector<SpaceTraders::Model::Agent::Agent> data;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ListAgents, data);
        }

        namespace Global
        {
            struct GetStatus
            {
                std::string status;
                std::string version;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetStatus, status, version);
        }
    }
}

template <class ResponseType>
void MakeRequest(httplib::Client& client, const std::string& path, ResponseType& content)
{
    httplib::Result result = client.Get(path);

    if (result->status == httplib::StatusCode::OK_200)
    {
        json temp = json::parse(result->body);
        content = temp.template get<ResponseType>();
    }
}

int main()
{
    const char* bearerToken = std::getenv("SPACE_TRADERS_TOKEN");
    if (!bearerToken)
    {
        std::cerr << "No bearer token specified. Is the SPACE_TRADERS_TOKEN environment variable set?" << std::endl;
        return 0;
    }

    httplib::Client client("https://api.spacetraders.io");
    client.set_bearer_token_auth(bearerToken);

    SpaceTraders::Endpoint::Global::GetStatus status;
    MakeRequest(client, "/v2/", status);

    std::cout << "Status: " << status.status << std::endl << "Version: " << status.version << std::endl;

    SpaceTraders::Endpoint::Agent::ListAgents agents;
    MakeRequest(client, "/v2/agents", agents);

    std::cout << "Count agents: " << agents.data.size() << std::endl;
}
