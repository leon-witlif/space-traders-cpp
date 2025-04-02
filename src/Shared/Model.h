#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <optional>
#include <string>

#include "nlohmann/json.hpp"

namespace SpaceTraders
{
    namespace Model::Agent
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

    namespace Model::Contract
    {
        struct ContractPayment
        {
            int32_t onAccepted;
            int32_t onFulfilled;
        };

        struct ContractDeliverGood
        {
            std::string tradeSymbol;
            std::string destinationSymbol;
            int32_t unitsRequired;
            int32_t unitsFulfilled;
        };

        struct ContractTerms
        {
            std::string deadline;
            ContractPayment payment;
            std::vector<ContractDeliverGood> deliver;
        };

        struct Contract
        {
            std::string id;
            std::string factionSymbol;
            std::string type;
            ContractTerms terms;
            bool accepted;
            bool fulfilled;
            std::string deadlineToAccept;
        };

        void from_json(const nlohmann::json& json, ContractPayment& payment);
        void from_json(const nlohmann::json& json, ContractDeliverGood& deliverGood);
        void from_json(const nlohmann::json& json, ContractTerms& terms);
        void from_json(const nlohmann::json& json, Contract& contract);
    }

    namespace Model::Faction
    {
    }

    namespace Model::Fleet
    {
        struct ShipRegistration
        {
            std::string name;
            std::string factionSymbol;
            std::string role;
        };

        struct ShipNavRouteWaypoint
        {
            std::string symbol;
            std::string type;
            std::string systemSymbol;
            int32_t x;
            int32_t y;
        };

        struct ShipNavRoute
        {
            ShipNavRouteWaypoint destination;
            ShipNavRouteWaypoint origin;
            std::string departureTime;
            std::string arrival;
        };

        struct ShipNav
        {
            std::string systemSymbol;
            std::string waypointSymbol;
            ShipNavRoute route;
            std::string status;
            std::string flightMode;
        };

        struct ShipCrew
        {
            int32_t current;
            int32_t required;
            int32_t capacity;
            std::string rotation;
            int32_t morale;
            int32_t wages;
        };

        struct ShipFuel
        {
            int32_t current;
            int32_t capacity;
            // consumed
        };

        struct Ship
        {
            std::string symbol;
            ShipRegistration registration;
            ShipNav nav;
            ShipCrew crew;
            // frame
            // reactor
            // engine
            // cooldown
            // modules
            // mounts
            // cargo
            ShipFuel fuel;
        };

        void from_json(const nlohmann::json& json, ShipRegistration& registration);
        void from_json(const nlohmann::json& json, ShipNavRouteWaypoint& routeWaypoint);
        void from_json(const nlohmann::json& json, ShipNavRoute& route);
        void from_json(const nlohmann::json& json, ShipNav& nav);
        void from_json(const nlohmann::json& json, ShipCrew& crew);
        void from_json(const nlohmann::json& json, ShipFuel& fuel);
        void from_json(const nlohmann::json& json, Ship& ship);
    }

    namespace Model::System
    {
    }

    namespace Model::Data
    {
    }

    namespace Model::Global
    {
        struct Status
        {
            std::string status;
            std::string version;
            std::string resetDate;
            std::string description;
        };

        void from_json(const nlohmann::json& json, Status& status);
    }
}

#endif
