#include "nlohmann/json.hpp"

#include "Model/Agent.h"

namespace SpaceTraders::Model::Agent
{
    void from_json(const nlohmann::json& json, Agent& agent)
    {
        json.contains("accountId") ? agent.accountId = json.at("accountId").get<std::string>() : agent.accountId = std::nullopt;
        json.at("symbol").get_to(agent.symbol);
        json.at("headquarters").get_to(agent.headquarters);
        json.at("credits").get_to(agent.credits);
        json.at("startingFaction").get_to(agent.startingFaction);
        json.at("shipCount").get_to(agent.shipCount);
    }
}
