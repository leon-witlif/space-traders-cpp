#include "SpaceTraders.h"

#include <iostream>

#include "HttpClient.h"

void SpaceTraders::Model::Agent::from_json(const nlohmann::json& json, SpaceTraders::Model::Agent::Agent& agent)
{
    json.contains("accountId") ? agent.accountId = json.at("accountId").get<std::string>() : agent.accountId = std::nullopt;
}

void SpaceTraders::Endpoint::Agent::from_json(const nlohmann::json& json, SpaceTraders::Endpoint::Agent::ListAgents& agents)
{
    json.at("data").get_to(agents.data);
}

void SpaceTraders::Endpoint::Global::from_json(const nlohmann::json& json, SpaceTraders::Endpoint::Global::GetStatus& status)
{
    json.at("status").get_to(status.status);
    json.at("version").get_to(status.version);
}

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

    std::cout << "Status: " << status.status << std::endl << "Version: " << status.version << std::endl;

    client.MakeRequest("/agents", response);
    auto agents = response.template get<SpaceTraders::Endpoint::Agent::ListAgents>();

    std::cout << "Count agents: " << agents.data.size() << std::endl;
}
