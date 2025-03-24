#ifndef MODEL_AGENT_H
#define MODEL_AGENT_H
#pragma once

#include <optional>
#include <string>

#include "nlohmann/json_fwd.hpp"

namespace SpaceTraders::Model::Agent
{
    struct Agent
    {
        std::optional<std::string> accountId;
        std::string symbol;
        std::string headquarters;
        int64_t credits;
        std::string startingFaction;
        int32_t shipCount;
    };

    void from_json(const nlohmann::json& json, Agent& agent);
}

#endif
