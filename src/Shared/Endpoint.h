#ifndef ENDPOINT_H
#define ENDPOINT_H
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "HttpClient.h"
#include "Model.h"

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        std::optional<Model::Agent::Agent> GetAgent(HttpClient& client, const std::string& agentToken);
        std::vector<Model::Agent::Agent> ListAgents(HttpClient& client);
        // Model::Agent::Agent GetPublicAgent(HttpClient& client);
    }

    namespace Endpoint::Contract
    {
        std::vector<Model::Contract::Contract> ListContracts(HttpClient& client, const std::string& agentToken);
        std::optional<Model::Contract::Contract> GetContract(HttpClient& client, const std::string& agentToken, const std::string& id);
        void AcceptContract(HttpClient& client, const std::string& agentToken, const Model::Contract::Contract& contract);
        // void DeliverCargoToContract();
        // void FulfillContract();
    }

    namespace Endpoint::Faction
    {
    }

    namespace Endpoint::Fleet
    {
        std::vector<Model::Fleet::Ship> ListShips(HttpClient& client, const std::string& agentToken);
        void PatchShipNav(HttpClient& client, const std::string& agentToken, const Model::Fleet::Ship& ship, const std::string& flightMode);
    }

    namespace Endpoint::System
    {
    }

    namespace Endpoint::Data
    {
    }

    namespace Endpoint::Global
    {
        std::optional<Model::Global::Status> GetStatus(HttpClient& client);
    }
}

#endif
