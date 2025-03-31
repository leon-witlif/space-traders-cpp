#include "HttpClient.h"

SpaceTraders::HttpClient::HttpClient(const std::string bearerToken)
    : client("https://api.spacetraders.io"), bearerToken(bearerToken)
{
}

void SpaceTraders::HttpClient::MakeGlobalRequest(const std::string& path, nlohmann::json& content)
{
    client.set_bearer_token_auth(bearerToken);
    MakeRequest(path, content);
}

void SpaceTraders::HttpClient::MakeAccountRequest(const std::string& agentToken, const std::string& path, nlohmann::json& content)
{
    client.set_bearer_token_auth(agentToken);
    MakeRequest(path, content);
}

void SpaceTraders::HttpClient::MakeRequest(const std::string& path, nlohmann::json& content)
{
    httplib::Result result = client.Get("/v2" + path);

    std::cout << path << ": " << result->status << std::endl;

    if (result->status == httplib::StatusCode::OK_200)
    {
        content = nlohmann::json::parse(result->body);
    }
}
