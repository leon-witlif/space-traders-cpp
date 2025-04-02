#include <iostream>

#include "HttpClient.h"
#include "Window.h"

int main()
{
    const std::string bearerToken = std::getenv("SPACE_TRADERS_TOKEN");
    if (!bearerToken.length())
    {
        std::cerr << "No bearer token specified. Is the SPACE_TRADERS_TOKEN environment variable set?" << std::endl;
        return -1;
    }

    const std::string agentToken("");

    SpaceTraders::HttpClient client(bearerToken);
    SpaceTraders::Window window(client, agentToken);

    window.RunWindowLoop();
}
