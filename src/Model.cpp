#include "nlohmann/json.hpp"

#include "Model.h"

namespace SpaceTraders
{
    namespace Model::Agent
    {
        void from_json(const nlohmann::json& json, Agent& agent)
        {
            json.contains("accountId") ? agent.accountId = json.at("accountId").get<std::string>() : agent.accountId = std::nullopt;
            json.at("symbol").get_to(agent.symbol);
            json.at("headquarters").get_to(agent.headquarters);
            json.at("credits").get_to(agent.credits);
            json.at("startingFaction").get_to(agent.startingFaction);
            json.at("shipCount").get_to(agent.shipCount);
        }
    }

    namespace Model::Fleet
    {
        void from_json(const nlohmann::json& json, ShipRegistration& registration)
        {
            json.at("name").get_to(registration.name);
            json.at("factionSymbol").get_to(registration.factionSymbol);
            json.at("role").get_to(registration.role);
        }

        void from_json(const nlohmann::json& json, ShipCrew& crew)
        {
            json.at("current").get_to(crew.current);
            json.at("required").get_to(crew.required);
            json.at("capacity").get_to(crew.capacity);
            json.at("rotation").get_to(crew.rotation);
            json.at("morale").get_to(crew.morale);
            json.at("wages").get_to(crew.wages);
        }

        void from_json(const nlohmann::json& json, ShipFuel& fuel)
        {
            json.at("current").get_to(fuel.current);
            json.at("capacity").get_to(fuel.capacity);
            // consumed
        }

        void from_json(const nlohmann::json& json, Ship& ship)
        {
            json.at("symbol").get_to(ship.symbol);
            json.at("registration").get_to(ship.registration);
            // nav
            json.at("crew").get_to(ship.crew);
            // frame
            // reactor
            // engine
            // cooldown
            // modules
            // mounts
            // cargo
            json.at("fuel").get_to(ship.fuel);
        }
    }
}
