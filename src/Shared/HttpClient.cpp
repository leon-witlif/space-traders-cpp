#include "HttpClient.h"

SpaceTraders::HttpClient::HttpClient(const std::string& bearerToken)
    : m_Client("https://api.spacetraders.io"), m_BearerToken(bearerToken)
{
}

nlohmann::json SpaceTraders::HttpClient::GlobalGetRequest(const std::string& path)
{
    m_Client.set_bearer_token_auth(m_BearerToken);
    return GetRequest(path);
}

nlohmann::json SpaceTraders::HttpClient::AccountGetRequest(const std::string& agentToken, const std::string& path)
{
    m_Client.set_bearer_token_auth(agentToken);
    return GetRequest(path);
}

nlohmann::json SpaceTraders::HttpClient::AccountPostRequest(const std::string& agentToken, const std::string& path, const nlohmann::json* body)
{
    m_Client.set_bearer_token_auth(agentToken);
    return PostRequest(path, body);
}

void SpaceTraders::HttpClient::AccountPatchRequest(const std::string& agentToken, const std::string& path, const nlohmann::json* body)
{
    m_Client.set_bearer_token_auth(agentToken);
    PatchRequest(path, body);
}

nlohmann::json SpaceTraders::HttpClient::GetRequest(const std::string& path)
{
    httplib::Result result = m_Client.Get("/v2" + path);

    std::cout << "GET " << path << ": " << result->status << std::endl;

    return nlohmann::json::parse(result->body);
}

nlohmann::json SpaceTraders::HttpClient::PostRequest(const std::string& path, const nlohmann::json* body)
{
    httplib::Result result = body
        ? m_Client.Post("/v2" + path, body->dump(), "application/json")
        : m_Client.Post("/v2" + path);

    std::cout << "POST " << path << ": " << result->status << std::endl;

    return nlohmann::json::parse(result->body);
}

void SpaceTraders::HttpClient::PatchRequest(const std::string& path, const nlohmann::json* body)
{
    httplib::Result result = body
        ? m_Client.Patch("/v2" + path, body->dump(), "application/json")
        : m_Client.Patch("/v2" + path);

    std::cout << "PATCH " << path << ": " << result->status << std::endl;
}
