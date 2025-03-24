#include "nlohmann/json.hpp"

#include "Endpoint/Agent.h"
#include "Endpoint/Global.h"

namespace SpaceTraders::Endpoint::Agent
{
    void from_json(const nlohmann::json& json, GetAgent& agent)
    {
    }

    void from_json(const nlohmann::json& json, ListAgents& agents)
    {
        json.at("data").get_to(agents.data);
    }

    void from_json(const nlohmann::json& json, GetPublicAgent& agent)
    {
    }
}

namespace SpaceTraders::Endpoint::Global
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
