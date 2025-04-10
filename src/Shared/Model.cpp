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
        void from_json(const nlohmann::json& json, Cooldown& cooldown)
        {
            json.at("shipSymbol").get_to(cooldown.shipSymbol);
            json.at("totalSeconds").get_to(cooldown.totalSeconds);
            json.at("remainingSeconds").get_to(cooldown.remainingSeconds);
            json.contains("expiration") ? cooldown.expiration = json.at("expiration").get<std::string>() : cooldown.expiration = std::nullopt;
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
            json.at("nav").get_to(ship.nav);
            json.at("crew").get_to(ship.crew);
            // frame
            // reactor
            // engine
            json.at("cooldown").get_to(ship.cooldown);
            // modules
            // mounts
            // cargo
            json.at("fuel").get_to(ship.fuel);
        }
    }
}
