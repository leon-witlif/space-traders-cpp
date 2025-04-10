#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <optional>
#include <string>

#include "nlohmann/json.hpp"

namespace SpaceTraders
{
    namespace Model
    {
        struct Meta
        {
            int32_t total;
            int32_t page;
            int32_t limit;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Meta, total, page, limit);
    }

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

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContractPayment, onAccepted, onFulfilled);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContractDeliverGood, tradeSymbol, destinationSymbol, unitsRequired, unitsFulfilled);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContractTerms, deadline, payment, deliver);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Contract, id, factionSymbol, type, terms, accepted, fulfilled, deadlineToAccept);
    }

    namespace Model::Faction
    {
        struct FactionTrait
        {
            std::string symbol;
            std::string name;
            std::string description;
        };

        struct Faction
        {
            std::string symbol;
            std::string name;
            std::string description;
            std::optional<std::string> headquarters;
            std::vector<FactionTrait> traits;
            bool isRecruiting;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FactionTrait, symbol, name, description);
        void from_json(const nlohmann::json& json, Faction& faction);
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

        struct Cooldown
        {
            std::string shipSymbol;
            int32_t totalSeconds;
            int32_t remainingSeconds;
            std::optional<std::string> expiration;
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
            Cooldown cooldown;
            // modules
            // mounts
            // cargo
            ShipFuel fuel;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipRegistration, name, factionSymbol, role);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipNavRouteWaypoint, symbol, type, systemSymbol, x, y);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipNavRoute, destination, origin, departureTime, arrival);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipNav, systemSymbol, waypointSymbol, route, status, flightMode);
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ShipCrew, current, required, capacity, rotation, morale, wages);
        void from_json(const nlohmann::json& json, Cooldown& cooldown);
        void from_json(const nlohmann::json& json, ShipFuel& fuel);
        void from_json(const nlohmann::json& json, Ship& ship);
    }

    namespace Model::System
    {
        struct Waypoint
        {
            std::string symbol;
            std::string type;
            std::string systemSymbol;
            int32_t x;
            int32_t y;
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Waypoint, symbol, type, systemSymbol, x, y);
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

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Status, status, version, resetDate, description);
    }
}

#endif
