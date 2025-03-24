#ifndef ENDPOINT_AGENT_H
#define ENDPOINT_AGENT_H
#pragma once

#include <vector>

#include "nlohmann/json_fwd.hpp"

#include "Model/Agent.h"

namespace SpaceTraders::Endpoint::Agent
{
    struct GetAgent
    {
    };

    struct ListAgents
    {
        std::vector<SpaceTraders::Model::Agent::Agent> data;
    };

    struct GetPublicAgent
    {
    };

    void from_json(const nlohmann::json& json, GetAgent& agent);
    void from_json(const nlohmann::json& json, ListAgents& agents);
    void from_json(const nlohmann::json& json, GetPublicAgent& agent);
}

#endif
