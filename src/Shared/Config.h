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
            ~Config();

            const std::string& GetBearerToken() const;
            const nlohmann::json::array_t& GetAgents() const;

            nlohmann::json& GetConfig();

        private:
            const std::string m_ConfigFilePath;
            nlohmann::json m_Config;
    };
}

#endif
