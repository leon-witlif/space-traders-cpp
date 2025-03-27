#include "nlohmann/json.hpp"

#include "Endpoint.h"

static nlohmann::json content;

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        Model::Agent::Agent GetAgent(HttpClient& client, const std::string& agentToken)
        {
            client.MakeAccountRequest(agentToken, "/my/agent", content);
            return content.at("data").template get<Model::Agent::Agent>();
        }

        std::vector<Model::Agent::Agent> ListAgents(HttpClient& client)
        {
            client.MakeGlobalRequest("/agents", content);
            return content.at("data").template get<std::vector<Model::Agent::Agent>>();
            // array{meta: array{total: int32, page: int32, limit: int32}}
        }
    }

    namespace Endpoint::Fleet
    {
        std::vector<Model::Fleet::Ship> ListShips(HttpClient& client, const std::string& agentToken)
        {
            client.MakeAccountRequest(agentToken, "/my/ships", content);
            return content.at("data").template get<std::vector<Model::Fleet::Ship>>();
            // array{meta: array{total: int32, page: int32, limit: int32}}
        }
    }

    namespace Endpoint::Global
    {
        Model::Global::Status GetStatus(HttpClient& client)
        {
            client.MakeGlobalRequest("/", content);
            return content.template get<Model::Global::Status>();
        }
    }
}
