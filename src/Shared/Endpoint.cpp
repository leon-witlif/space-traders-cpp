#include "Endpoint.h"

static nlohmann::json content;

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        Model::Agent::Agent GetAgent(HttpClient& client, const std::string& agentToken)
        {
            client.AccountGetRequest(agentToken, "/my/agent", content);
            return content.at("data").template get<Model::Agent::Agent>();
        }

        std::vector<Model::Agent::Agent> ListAgents(HttpClient& client)
        {
            client.GlobalGetRequest("/agents", content);
            return content.at("data").template get<std::vector<Model::Agent::Agent>>();
            // array{meta: array{total: int32, page: int32, limit: int32}}
        }
    }

    namespace Endpoint::Contract
    {
        std::vector<Model::Contract::Contract> ListContracts(HttpClient& client, const std::string& agentToken)
        {
            client.AccountGetRequest(agentToken, "/my/contracts", content);
            return content.at("data").template get<std::vector<Model::Contract::Contract>>();
            // array{meta: array{total: int32, page: int32, limit: int32}}
        }

        Model::Contract::Contract GetContract(HttpClient& client, const std::string& agentToken, const std::string& id)
        {
            client.AccountGetRequest(agentToken, "/my/contracts/" + id, content);
            return content.at("data").template get<Model::Contract::Contract>();
        }

        void AcceptContract(HttpClient& client, const std::string& agentToken, const Model::Contract::Contract& contract)
        {
            client.AccountPostRequest(agentToken, "/my/contracts/" + contract.id + "/accept");
        }
    }

    namespace Endpoint::Fleet
    {
        std::vector<Model::Fleet::Ship> ListShips(HttpClient& client, const std::string& agentToken)
        {
            client.AccountGetRequest(agentToken, "/my/ships", content);
            return content.at("data").template get<std::vector<Model::Fleet::Ship>>();
            // array{meta: array{total: int32, page: int32, limit: int32}}
        }

        void PatchShipNav(HttpClient& client, const std::string& agentToken, const Model::Fleet::Ship& ship, const std::string& flightMode)
        {
            const nlohmann::json json = { {"flightMode", flightMode} };

            client.AccountPatchRequest(agentToken, "/my/ships/" + ship.symbol + "/nav", json);
        }
    }

    namespace Endpoint::Global
    {
        Model::Global::Status GetStatus(HttpClient& client)
        {
            client.GlobalGetRequest("/", content);
            return content.template get<Model::Global::Status>();
        }
    }
}
