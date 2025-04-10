#include "Config.h"

SpaceTraders::Config::Config(const std::string& configPath)
    : m_ConfigFilePath(configPath)
{
    std::ifstream configFile(m_ConfigFilePath);
    m_Config = nlohmann::json::parse(configFile);
    configFile.close();
}

SpaceTraders::Config::~Config()
{
    std::ofstream configFile(m_ConfigFilePath, std::ios::out | std::ios::trunc);
    configFile << m_Config.dump(4) << std::endl;
    configFile.close();
}

const std::string& SpaceTraders::Config::GetBearerToken() const
{
    const std::string& token = m_Config.at("accountBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "No account bearer token specified. Is the config variable set?" << std::endl;
    }

    return token;
}

const std::string& SpaceTraders::Config::GetAgentToken() const
{
    const std::string& token = m_Config.at("agentBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "No agent bearer token specified. Is the config value set?" << std::endl;
    }

    return token;
}

nlohmann::json& SpaceTraders::Config::GetConfig()
{
    return m_Config;
}
