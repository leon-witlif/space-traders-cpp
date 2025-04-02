#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

volatile std::sig_atomic_t isRunning = 1;

void SignalHandler(int signal)
{
    isRunning = 0;
}

int main()
{
    std::signal(SIGINT, SignalHandler);

    while (isRunning)
    {
        std::cout << "Processing..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
