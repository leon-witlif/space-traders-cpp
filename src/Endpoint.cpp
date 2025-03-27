#include "nlohmann/json.hpp"

#include "Endpoint.h"

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        void from_json(const nlohmann::json& json, GetAgent& agent)
        {
            json.at("data").get_to(agent.data);
        }

        void from_json(const nlohmann::json& json, ListAgents& agents)
        {
            json.at("data").get_to(agents.data);
        }

        void from_json(const nlohmann::json& json, GetPublicAgent& agent)
        {
            json.at("data").get_to(agent.data);
        }
    }

    namespace Endpoint::Fleet
    {
        void from_json(const nlohmann::json& json, ListShips& ships)
        {
            json.at("data").get_to(ships.data);
        }
    }

    namespace Endpoint::Global
    {
        void from_json(const nlohmann::json& json, GetStatus& status)
        {
            json.at("status").get_to(status.status);
            json.at("version").get_to(status.version);
            json.at("resetDate").get_to(status.resetDate);
            json.at("description").get_to(status.description);
        }

        void from_json(const nlohmann::json& json, RegisterNewAgent& agent)
        {
        }
    }
}
