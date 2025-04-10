#ifndef ENDPOINT_H
#define ENDPOINT_H
#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "nlohmann/json.hpp"

#include "HttpClient.h"
#include "Model.h"

#define GLOBAL_ACTION SpaceTraders::HttpClient& client
#define AGENT_ACTION SpaceTraders::HttpClient& client, const std::string& agentToken

namespace SpaceTraders
{
    namespace Endpoint::Agent
    {
        std::optional<Model::Agent::Agent> GetAgent(AGENT_ACTION);
        std::pair<std::vector<Model::Agent::Agent>, Model::Meta> ListAgents(GLOBAL_ACTION);
        // Model::Agent::Agent GetPublicAgent(GLOBAL_ACTION);
    }

    namespace Endpoint::Contract
    {
        std::pair<std::vector<Model::Contract::Contract>, Model::Meta> ListContracts(AGENT_ACTION);
        std::optional<Model::Contract::Contract> GetContract(AGENT_ACTION, const std::string& id);
        void AcceptContract(AGENT_ACTION, const Model::Contract::Contract& contract);
        // void DeliverCargoToContract();
        // void FulfillContract();
    }

    namespace Endpoint::Faction
    {
    }

    namespace Endpoint::Fleet
    {
        std::pair<std::vector<Model::Fleet::Ship>, Model::Meta> ListShips(AGENT_ACTION);
        void OrbitShip(AGENT_ACTION, const Model::Fleet::Ship& ship);
        void CreateChart(AGENT_ACTION, const Model::Fleet::Ship& ship);
        void DockShip(AGENT_ACTION, const Model::Fleet::Ship& ship);
        void CreateSurvey(AGENT_ACTION, const Model::Fleet::Ship& ship);
        void NavigateShip(AGENT_ACTION, const Model::Fleet::Ship& ship, const std::string& waypointSymbol);
        void PatchShipNav(AGENT_ACTION, const Model::Fleet::Ship& ship, const std::string& flightMode);
        void NegotiateContract(AGENT_ACTION, const Model::Fleet::Ship& ship);
    }

    namespace Endpoint::System
    {
        std::pair<std::vector<Model::System::Waypoint>, Model::Meta> ListWaypointsInSystem(AGENT_ACTION, const std::string& systemSymbol, int32_t page = 1, int32_t limit = 10);
    }

    namespace Endpoint::Data
    {
    }

    namespace Endpoint::Global
    {
        std::optional<Model::Global::Status> GetStatus(GLOBAL_ACTION);
    }
}

#endif
