#include "Config.h"

SpaceTraders::Config::Config(const std::string& configPath)
{
    std::ifstream file(configPath);
    m_Config = nlohmann::json::parse(file);
    file.close();
}

const std::string& SpaceTraders::Config::GetBearerToken()
{
    const std::string& token = m_Config.at("accountBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "No account bearer token specified. Is the config variable set?" << std::endl;
    }

    return token;
}

const std::string& SpaceTraders::Config::GetAgentToken()
{
    const std::string& token = m_Config.at("agentBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "No agent bearer token specified. Is the config value set?" << std::endl;
    }

    return token;
}
