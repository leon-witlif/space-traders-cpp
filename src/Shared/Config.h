#ifndef CONFIG_H
#define CONFIG_H
#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "nlohmann/json.hpp"

namespace SpaceTraders
{
    class Config
    {
        public:
            Config(const std::string& configPath);

            const std::string& GetBearerToken();
            const std::string& GetAgentToken();

        private:
            nlohmann::json m_Config;
    };
}

#endif
