#include <iostream>

#include "Endpoint.h"
#include "HttpClient.h"
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

    auto status = SpaceTraders::Endpoint::Global::GetStatus(client);
    // auto agents = SpaceTraders::Endpoint::Agent::ListAgents(client);

    SpaceTraders::Model::Agent::Agent agent{};
    std::vector<SpaceTraders::Model::Fleet::Ship> ships{};
    std::vector<SpaceTraders::Model::Contract::Contract> contracts{};

    if (agentToken.length())
    {
        agent = SpaceTraders::Endpoint::Agent::GetAgent(client, agentToken);
        ships = SpaceTraders::Endpoint::Fleet::ListShips(client, agentToken);
        contracts = SpaceTraders::Endpoint::Contract::ListContracts(client, agentToken);
    }

    SpaceTraders::Window window(&status, &agent, &ships, &contracts);
    window.RunWindowLoop();
}
