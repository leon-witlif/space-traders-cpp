#include <fstream>
#include <iostream>
#include <cmath>

#include "Config.h"
#include "HttpClient.h"
#include "Window.h"

#define EXPERIMENTAL_FEATURES 0

#if EXPERIMENTAL_FEATURES
int32_t distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    return std::ceil(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)));
}
#endif

int main()
{
    SpaceTraders::Config config("config.json");
    SpaceTraders::HttpClient client(config.GetBearerToken());

#if EXPERIMENTAL_FEATURES
    config.GetConfig()["waypoints"] = nlohmann::json::array();
    auto& waypoints = config.GetConfig()["waypoints"];

    int32_t page = 1;
    int32_t limit = 20;

    auto response = SpaceTraders::Endpoint::System::ListWaypointsInSystem(client, config.GetAgentToken(), "X1-GU83", page, limit);
    auto headquarters = response.first[0];

    while (response.second.page * limit < response.second.total)
    {
        for (const auto& waypoint : response.first)
        {
            nlohmann::json json = waypoint;
            json["distance"] = distance(headquarters.x, headquarters.y, waypoint.x, waypoint.y);

            waypoints.push_back(json);
        }

        ++page;
        response = SpaceTraders::Endpoint::System::ListWaypointsInSystem(client, config.GetAgentToken(), "X1-GU83", page, limit);
    }
#endif

    SpaceTraders::Window window(client, config);
    window.RunWindowLoop();
}
