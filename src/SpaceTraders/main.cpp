#include <fstream>
#include <iostream>

#include "Config.h"
#include "HttpClient.h"
#include "Window.h"

int main()
{
    SpaceTraders::Config config("config.json");
    SpaceTraders::HttpClient client(config.GetBearerToken());
    SpaceTraders::Window window(client, config.GetAgentToken());

    window.RunWindowLoop();
}
