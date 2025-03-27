#ifndef ENDPOINT_H
#define ENDPOINT_H
#pragma once

#include <vector>

#include "nlohmann/json_fwd.hpp"

#include "Model.h"

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        struct GetAgent
        {
            Model::Agent::Agent data;
        };

        struct ListAgents
        {
            std::vector<Model::Agent::Agent> data;
            // array{meta: array{total: int32, page: int32, limit: int32}}
        };

        struct GetPublicAgent
        {
            Model::Agent::Agent data;
        };

        void from_json(const nlohmann::json& json, GetAgent& agent);
        void from_json(const nlohmann::json& json, ListAgents& agents);
        void from_json(const nlohmann::json& json, GetPublicAgent& agent);
    }

    namespace Endpoint::Contract
    {
    }

    namespace Endpoint::Faction
    {
    }

    namespace Endpoint::Fleet
    {
        struct ListShips
        {
            std::vector<Model::Fleet::Ship> data;
            // array{meta: array{total: int32, page: int32, limit: int32}}
        };

        void from_json(const nlohmann::json& json, ListShips& ships);
    }

    namespace Endpoint::System
    {
    }

    namespace Endpoint::Data
    {
    }

    namespace Endpoint::Global
    {
        struct GetStatus
        {
            std::string status;
            std::string version;
            std::string resetDate;
            std::string description;
        };

        struct RegisterNewAgent
        {
        };

        void from_json(const nlohmann::json& json, GetStatus& status);
        void from_json(const nlohmann::json& json, RegisterNewAgent& agent);
    }
}

#endif
