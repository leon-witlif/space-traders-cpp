#include <iostream>

#include "nlohmann/json.hpp"

#include "HttpClient.h"
#include "Endpoint.h"
#include "Window.h"

int main()
{
    const char* bearerToken = std::getenv("SPACE_TRADERS_TOKEN");
    if (!bearerToken)
    {
        std::cerr << "No bearer token specified. Is the SPACE_TRADERS_TOKEN environment variable set?" << std::endl;
        return -1;
    }

    std::string agentToken("");

    SpaceTraders::HttpClient client(bearerToken);
    nlohmann::json content;

    auto status = SpaceTraders::Endpoint::Global::GetStatus(client);
    // auto agents = SpaceTraders::Endpoint::Agent::ListAgents(client);

    SpaceTraders::Model::Agent::Agent agent{};
    std::vector<SpaceTraders::Model::Fleet::Ship> ships{};

    if (agentToken.length())
    {
        agent = SpaceTraders::Endpoint::Agent::GetAgent(client, agentToken);
        ships = SpaceTraders::Endpoint::Fleet::ListShips(client, agentToken);
    }

    SpaceTraders::Window window(&status, &agent, &ships);
    window.RunWindowLoop();
}
