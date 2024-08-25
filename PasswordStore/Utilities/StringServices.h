#pragma once

#include <string>
#include <unordered_map>
#include <vector>


namespace String
{
    // Using Declarations
    //
    using Vector = std::vector<std::string>;

    // String Constants
    //
    const std::string ENDPOINT = "Endpoint";

    // Helper Methods
    //
    std::unordered_map<std::string, std::string> explodeRequest(
        const std::string& theString);

    Vector split(const std::string& theString, const char delim);

    std::string endPoint(const std::string& endPointString);
}; 