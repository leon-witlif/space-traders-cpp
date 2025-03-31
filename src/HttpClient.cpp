#include "HttpClient.h"

SpaceTraders::HttpClient::HttpClient(const std::string& bearerToken)
    : m_Client("https://api.spacetraders.io"), m_BearerToken(bearerToken)
{
}

void SpaceTraders::HttpClient::GlobalGetRequest(const std::string& path, nlohmann::json& content)
{
    m_Client.set_bearer_token_auth(m_BearerToken);
    GetRequest(path, content);
}

void SpaceTraders::HttpClient::AccountGetRequest(const std::string& agentToken, const std::string& path, nlohmann::json& content)
{
    m_Client.set_bearer_token_auth(agentToken);
    GetRequest(path, content);
}

void SpaceTraders::HttpClient::AccountPostRequest(const std::string& agentToken, const std::string& path)
{
    m_Client.set_bearer_token_auth(agentToken);
    PostRequest(path);
}

void SpaceTraders::HttpClient::AccountPatchRequest(const std::string& agentToken, const std::string& path, const nlohmann::json& json)
{
    m_Client.set_bearer_token_auth(agentToken);
    PatchRequest(path, json);
}

void SpaceTraders::HttpClient::GetRequest(const std::string& path, nlohmann::json& content)
{
    httplib::Result result = m_Client.Get("/v2" + path);

    std::cout << "GET " << path << ": " << result->status << std::endl;

    if (result->status == httplib::StatusCode::OK_200)
    {
        content = nlohmann::json::parse(result->body);
    }
}

void SpaceTraders::HttpClient::PostRequest(const std::string& path)
{
    httplib::Result result = m_Client.Post("/v2" + path);

    std::cout << "POST " << path << ": " << result->status << std::endl;
}

void SpaceTraders::HttpClient::PatchRequest(const std::string& path, const nlohmann::json& json)
{
    httplib::Result result = m_Client.Patch("/v2" + path, json.dump(), "application/json");

    std::cout << "PATCH " << path << ": " << result->status << std::endl;
}
