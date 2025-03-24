#ifndef ENDPOINT_GLOBAL_H
#define ENDPOINT_GLOBAL_H
#pragma once

#include <string>

#include "nlohmann/json_fwd.hpp"

namespace SpaceTraders::Endpoint::Global
{
    struct GetStatus
    {
        std::string status;
        std::string version;
        std::string resetDate;
        std::string description;
    };

    struct RegisterNewAgent
    {
    };

    void from_json(const nlohmann::json& json, GetStatus& status);
    void from_json(const nlohmann::json& json, RegisterNewAgent& agent);
}

#endif
