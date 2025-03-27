#ifndef ENDPOINT_H
#define ENDPOINT_H
#pragma once

#include <vector>

#include "nlohmann/json_fwd.hpp"

#include "HttpClient.h"
#include "Model.h"

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        Model::Agent::Agent GetAgent(HttpClient& client, const std::string& agentToken);
        std::vector<Model::Agent::Agent> ListAgents(HttpClient& client);
        // Model::Agent::Agent GetPublicAgent(HttpClient& client);
    }

    namespace Endpoint::Contract
    {
    }

    namespace Endpoint::Faction
    {
    }

    namespace Endpoint::Fleet
    {
        std::vector<Model::Fleet::Ship> ListShips(HttpClient& client, const std::string& agentToken);
    }

    namespace Endpoint::System
    {
    }

    namespace Endpoint::Data
    {
    }

    namespace Endpoint::Global
    {
        Model::Global::Status GetStatus(HttpClient& client);
    }
}

#endif
