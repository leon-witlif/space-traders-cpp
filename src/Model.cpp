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

    namespace Model::Contract
    {
        void from_json(const nlohmann::json& json, ContractPayment& payment)
        {
            json.at("onAccepted").get_to(payment.onAccepted);
            json.at("onFulfilled").get_to(payment.onFulfilled);
        }

        void from_json(const nlohmann::json& json, ContractDeliverGood& deliverGood)
        {
            json.at("tradeSymbol").get_to(deliverGood.tradeSymbol);
            json.at("destinationSymbol").get_to(deliverGood.destinationSymbol);
            json.at("unitsRequired").get_to(deliverGood.unitsRequired);
            json.at("unitsFulfilled").get_to(deliverGood.unitsFulfilled);
        }

        void from_json(const nlohmann::json& json, ContractTerms& terms)
        {
            json.at("deadline").get_to(terms.deadline);
            json.at("payment").get_to(terms.payment);
            json.at("deliver").get_to(terms.deliver);
        }

        void from_json(const nlohmann::json& json, Contract& contract)
        {
            json.at("id").get_to(contract.id);
            json.at("factionSymbol").get_to(contract.factionSymbol);
            json.at("type").get_to(contract.type);
            json.at("terms").get_to(contract.terms);
            json.at("accepted").get_to(contract.accepted);
            json.at("fulfilled").get_to(contract.fulfilled);
            json.at("deadlineToAccept").get_to(contract.deadlineToAccept);
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

        void from_json(const nlohmann::json& json, ShipNavRouteWaypoint& routeWaypoint)
        {
            json.at("symbol").get_to(routeWaypoint.symbol);
            json.at("type").get_to(routeWaypoint.type);
            json.at("systemSymbol").get_to(routeWaypoint.systemSymbol);
            json.at("x").get_to(routeWaypoint.x);
            json.at("y").get_to(routeWaypoint.y);
        }

        void from_json(const nlohmann::json& json, ShipNavRoute& route)
        {
            json.at("destination").get_to(route.destination);
            json.at("origin").get_to(route.origin);
            json.at("departureTime").get_to(route.departureTime);
            json.at("arrival").get_to(route.arrival);
        }

        void from_json(const nlohmann::json& json, ShipNav& nav)
        {
            json.at("systemSymbol").get_to(nav.systemSymbol);
            json.at("waypointSymbol").get_to(nav.waypointSymbol);
            json.at("route").get_to(nav.route);
            json.at("status").get_to(nav.status);
            json.at("flightMode").get_to(nav.flightMode);
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
            json.at("nav").get_to(ship.nav);
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

    namespace Model::Global
    {
        void from_json(const nlohmann::json& json, Status& status)
        {
            json.at("status").get_to(status.status);
            json.at("version").get_to(status.version);
            json.at("resetDate").get_to(status.resetDate);
            json.at("description").get_to(status.description);
        }
    }
}
