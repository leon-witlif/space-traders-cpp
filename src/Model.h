#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <optional>
#include <string>

#include "nlohmann/json_fwd.hpp"

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
            // nav
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
