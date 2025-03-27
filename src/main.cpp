#include <iostream>

#include "nlohmann/json.hpp"

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
    nlohmann::json content;

    client.MakeGlobalRequest("/", content);
    auto status = content.template get<SpaceTraders::Endpoint::Global::GetStatus>();

    client.MakeGlobalRequest("/agents", content);
    auto agents = content.template get<SpaceTraders::Endpoint::Agent::ListAgents>();

    SpaceTraders::Endpoint::Agent::GetAgent agent{};
    SpaceTraders::Endpoint::Fleet::ListShips ships{};

    if (agentToken.length())
    {
        client.MakeAccountRequest(agentToken, "/my/agent", content);
        agent = content.template get<SpaceTraders::Endpoint::Agent::GetAgent>();

        client.MakeAccountRequest(agentToken, "/my/ships", content);
        ships = content.template get<SpaceTraders::Endpoint::Fleet::ListShips>();
    }

    SpaceTraders::Window window(&status, &agent, &ships);
    window.RunWindowLoop();
}
