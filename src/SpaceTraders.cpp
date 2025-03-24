#include <iostream>

#include "nlohmann/json.hpp"

#include "HttpClient.h"

int main()
{
    const char* bearerToken = std::getenv("SPACE_TRADERS_TOKEN");
    if (!bearerToken)
    {
        std::cerr << "No bearer token specified. Is the SPACE_TRADERS_TOKEN environment variable set?" << std::endl;
        return 0;
    }

    HttpClient client(bearerToken);
    nlohmann::json response;

    client.MakeRequest("/", response);
    auto status = response.template get<SpaceTraders::Endpoint::Global::GetStatus>();

    std::cout << "Status: " << status.status << std::endl 
        << "Version: " << status.version << std::endl
        << "ResetDate: " << status.resetDate << std::endl
        << "Description: " << status.description << std::endl << std::endl;

    client.MakeRequest("/agents", response);
    auto agents = response.template get<SpaceTraders::Endpoint::Agent::ListAgents>();

    std::cout << "Count agents: " << agents.data.size() << std::endl << std::endl;

    for (auto agent : agents.data)
    {
        std::cout << "AccountId: " << agent.accountId.value_or("Unknown") << std::endl
            << "Symbol: " << agent.symbol << std::endl
            << "Headquarters: " << agent.headquarters << std::endl
            << "Credits: " << agent.credits << std::endl
            << "StartingFaction" << agent.startingFaction << std::endl
            << "ShipCount: " << agent.shipCount << std::endl << std::endl;
    }
}
