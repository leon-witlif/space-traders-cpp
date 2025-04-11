#include "Endpoint.h"

#define TRY_RETURN(T) try { return response.template get<T>(); } catch (const nlohmann::json::exception& ex) { std::cerr << ex.what() << std::endl; }
#define TRY_RETURN_DATA(T) try { return response.at("data").template get<T>(); } catch (const nlohmann::json::exception& ex) { std::cerr << ex.what() << std::endl; }
#define TRY_RETURN_DATA_META(T) try { return std::make_pair(response.at("data").template get<T>(), response.at("meta").template get<Model::Meta>()); } catch (const nlohmann::json::exception& ex) { std::cerr << ex.what() << std::endl; }

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        std::optional<Model::Agent::Agent> GetAgent(AGENT_ACTION)
        {
            auto response = client.AccountGetRequest(agentToken, "/my/agent");
            TRY_RETURN_DATA(Model::Agent::Agent);
            return std::nullopt;
        }

        std::pair<std::vector<Model::Agent::Agent>, Model::Meta> ListAgents(GLOBAL_ACTION)
        {
            auto response = client.GlobalGetRequest("/agents");
            TRY_RETURN_DATA_META(std::vector<Model::Agent::Agent>);
            return {};
        }
    }

    namespace Endpoint::Contract
    {
        std::pair<std::vector<Model::Contract::Contract>, Model::Meta> ListContracts(AGENT_ACTION)
        {
            auto response = client.AccountGetRequest(agentToken, "/my/contracts");
            TRY_RETURN_DATA_META(std::vector<Model::Contract::Contract>);
            return {};
        }

        std::optional<Model::Contract::Contract> GetContract(AGENT_ACTION, const std::string& id)
        {
            auto response = client.AccountGetRequest(agentToken, "/my/contracts/" + id);
            TRY_RETURN_DATA(Model::Contract::Contract);
            return std::nullopt;
        }

        void AcceptContract(AGENT_ACTION, const Model::Contract::Contract& contract)
        {
            client.AccountPostRequest(agentToken, "/my/contracts/" + contract.id + "/accept");
        }
    }

    namespace Endpoint::Fleet
    {
        std::pair<std::vector<Model::Fleet::Ship>, Model::Meta> ListShips(AGENT_ACTION)
        {
            auto response = client.AccountGetRequest(agentToken, "/my/ships");
            TRY_RETURN_DATA_META(std::vector<Model::Fleet::Ship>);
            return {};
        }

        void OrbitShip(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/orbit");
        }

        void CreateChart(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            auto response = client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/chart");
            std::cout << response.dump(4) << std::endl;
        }

        void DockShip(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/dock");
        }

        void CreateSurvey(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            auto response = client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/survey");
            std::cout << response.dump(4) << std::endl;
        }

        void NavigateShip(AGENT_ACTION, const Model::Fleet::Ship& ship, const std::string& waypointSymbol)
        {
            const nlohmann::json body = { { "waypointSymbol", waypointSymbol } };
            auto response = client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/navigate", &body);
            std::cout << response.dump(4) << std::endl;
        }

        void PatchShipNav(AGENT_ACTION, const Model::Fleet::Ship& ship, const std::string& flightMode)
        {
            const nlohmann::json body = { { "flightMode", flightMode } };
            client.AccountPatchRequest(agentToken, "/my/ships/" + ship.symbol + "/nav", &body);
        }

        void RefuelShip(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/refuel");
        }

        void NegotiateContract(AGENT_ACTION, const Model::Fleet::Ship& ship)
        {
            client.AccountPostRequest(agentToken, "/my/ships/" + ship.symbol + "/negotiate/contract");
        }
    }

    namespace Endpoint::System
    {
        std::pair<std::vector<Model::System::Waypoint>, Model::Meta> ListWaypointsInSystem(AGENT_ACTION, const std::string& systemSymbol, int32_t page, int32_t limit)
        {
            auto response = client.AccountGetRequest(agentToken, "/systems/" + systemSymbol + "/waypoints?page=" + std::to_string(page) + "&limit=" + std::to_string(limit));
            TRY_RETURN_DATA_META(std::vector<Model::System::Waypoint>);
            return {};
        }
    }

    namespace Endpoint::Global
    {
        std::optional<Model::Global::Status> GetStatus(GLOBAL_ACTION)
        {
            auto response = client.GlobalGetRequest("/");
            TRY_RETURN(Model::Global::Status);
            return std::nullopt;
        }
    }
}
