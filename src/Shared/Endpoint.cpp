#include "Endpoint.h"

#define TRY_RETURN(T) try { return content.template get<T>(); } catch (const nlohmann::json::exception& ex) { std::cerr << ex.what() << std::endl; }
#define TRY_RETURN_DATA(T) try { return content.at("data").template get<T>(); } catch (const nlohmann::json::exception& ex) { std::cerr << ex.what() << std::endl; }

static nlohmann::json content;

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        std::optional<Model::Agent::Agent> GetAgent(HttpClient& client, const std::string& agentToken)
        {
            client.AccountGetRequest(agentToken, "/my/agent", content);
            TRY_RETURN_DATA(Model::Agent::Agent);
            return std::nullopt;
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
            TRY_RETURN_DATA(std::vector<Model::Contract::Contract>);
            // array{meta: array{total: int32, page: int32, limit: int32}}
            return {};
        }

        std::optional<Model::Contract::Contract> GetContract(HttpClient& client, const std::string& agentToken, const std::string& id)
        {
            client.AccountGetRequest(agentToken, "/my/contracts/" + id, content);
            TRY_RETURN_DATA(Model::Contract::Contract);
            return std::nullopt;
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
            TRY_RETURN_DATA(std::vector<Model::Fleet::Ship>);
            // array{meta: array{total: int32, page: int32, limit: int32}}
            return {};
        }

        void PatchShipNav(HttpClient& client, const std::string& agentToken, const Model::Fleet::Ship& ship, const std::string& flightMode)
        {
            const nlohmann::json json = { {"flightMode", flightMode} };

            client.AccountPatchRequest(agentToken, "/my/ships/" + ship.symbol + "/nav", json);
        }
    }

    namespace Endpoint::Global
    {
        std::optional<Model::Global::Status> GetStatus(HttpClient& client)
        {
            client.GlobalGetRequest("/", content);
            TRY_RETURN(Model::Global::Status);
            return std::nullopt;
        }
    }
}
