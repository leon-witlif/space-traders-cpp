#include "nlohmann/json.hpp"

#include "HttpClient.h"

HttpClient::HttpClient(const std::string& bearerToken)
    : client("https://api.spacetraders.io")
{
    client.set_bearer_token_auth(bearerToken);
}

void HttpClient::MakeRequest(const std::string& path, nlohmann::json& content)
{
    httplib::Result result = client.Get("/v2" + path);

    if (result->status == httplib::StatusCode::OK_200)
    {
        content = nlohmann::json::parse(result->body);
    }
}
