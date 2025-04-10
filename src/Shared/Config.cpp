#include "Config.h"

#define PRINT_ERROR_EXIT(e) std::cerr << e << std::endl; std::exit(EXIT_FAILURE)

SpaceTraders::Config::Config(const std::string& configPath)
    : m_ConfigFilePath(configPath)
{
    std::ifstream configFile(m_ConfigFilePath);
    if (!configFile.good())
    {
        PRINT_ERROR_EXIT("Unable to open " << configPath);
    }

    try
    {
        m_Config = nlohmann::json::parse(configFile);
    }
    catch (const nlohmann::json::exception& ex)
    {
        PRINT_ERROR_EXIT("Error while parsing " << configPath << ": " << ex.what());
    }

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
    if (!m_Config.contains("accountBearerToken"))
    {
        PRINT_ERROR_EXIT("No account bearer token specified. Is the config variable set?");
    }

    const std::string& token = m_Config.at("accountBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "Account bearer token is empty" << std::endl;
    }

    return token;
}

const std::string& SpaceTraders::Config::GetAgentToken() const
{
    if (!m_Config.contains("agentBearerToken"))
    {
        PRINT_ERROR_EXIT("No agent bearer token specified. Is the config value set?");
    }

    const std::string& token = m_Config.at("agentBearerToken").get_ref<const std::string&>();

    if (!token.length())
    {
        std::cerr << "Agent bearer token is empty" << std::endl;
    }

    return token;
}

nlohmann::json& SpaceTraders::Config::GetConfig()
{
    return m_Config;
}
