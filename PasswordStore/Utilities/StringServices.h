#pragma once

#include <string>
#include <unordered_map>
#include <vector>


namespace String
{
    using Vector = std::vector<std::string>;

    std::unordered_map<std::string, std::string> explodeRequest(
        const std::string& theString);

    Vector split(const std::string& theString, const char delim);

    std::string endPoint(const std::string& endPointString);
};
