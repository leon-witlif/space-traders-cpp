#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <thread>

#include "nlohmann/json.hpp"

#include "Config.h"
#include "HttpClient.h"
#include "Endpoint.h"

volatile std::sig_atomic_t isRunning = 1;

static std::chrono::time_point<std::chrono::system_clock> last, current;

void SignalHandler(int signal)
{
    isRunning = 0;
}

int main()
{
    std::signal(SIGINT, SignalHandler);

    SpaceTraders::Config config("config.json");
    SpaceTraders::HttpClient client(config.GetBearerToken());

    std::vector<SpaceTraders::Model::Contract::Contract> contracts;

    while (isRunning)
    {
        current = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(current - last);

        if (diff >= std::chrono::seconds(10))
        {
            last = current;

            contracts = SpaceTraders::Endpoint::Contract::ListContracts(client, config.GetAgentToken()).first;
            std::cout << contracts.size() << std::endl;
        }
    }
}
