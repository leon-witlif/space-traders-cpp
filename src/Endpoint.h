#ifndef ENDPOINT_H
#define ENDPOINT_H
#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

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
        std::vector<Model::Contract::Contract> ListContracts(HttpClient& client, const std::string& agentToken);
        Model::Contract::Contract GetContract(HttpClient& client, const std::string& agentToken);
        // void AcceptContract();
        // void DeliverCargoToContract();
        // void FulfillContract();
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
