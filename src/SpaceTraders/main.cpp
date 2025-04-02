#include <fstream>
#include <iostream>

#include "HttpClient.h"
#include "Window.h"

int main()
{
    std::ifstream configFile("config.json");
    nlohmann::json config = nlohmann::json::parse(configFile);
    configFile.close();

    std::string bearerToken = config.at("accountBearerToken").get<std::string>();
    if (!bearerToken.length())
    {
        std::cerr << "No account bearer token specified. Is the config variable set?" << std::endl;
    }

    std::string agentToken = config.at("agentBearerToken").get<std::string>();
    if (!agentToken.length())
    {
        std::cerr << "No agent bearer token specified. Is the config value set?" << std::endl;
    }

    SpaceTraders::HttpClient client(bearerToken);
    SpaceTraders::Window window(client, agentToken);

    window.RunWindowLoop();
}
