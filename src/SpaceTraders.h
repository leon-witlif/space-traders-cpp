#ifndef SPACE_TRADERS_H
#define SPACE_TRADERS_H
#pragma once

#include <optional>
#include <string>

#include "nlohmann/json.hpp"

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

            void from_json(const nlohmann::json& json, Agent& agent);
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

            void from_json(const nlohmann::json& json, ListAgents& agents);
        }

        namespace Global
        {
            struct GetStatus
            {
                std::string status;
                std::string version;
            };

            void from_json(const nlohmann::json& json, GetStatus& status);
        }
    }
}

#endif
