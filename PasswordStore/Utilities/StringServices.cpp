#include "StringServices.h"

#include <vector>
#include <sstream>


std::unordered_map<std::string, std::string> String::explodeRequest(
    const std::string& theString)
{
    std::unordered_map<std::string, std::string> result;

    std::stringstream inputString(theString);
    std::string line;

    while(std::getline(inputString, line))
    {
        // Remove those pesky carriage returns.
        //
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (!line.empty())
        {
            constexpr char delim = ':';
            const String::Vector data = String::split(line, delim);

            if (data.size() == 1)
            {
                result.emplace("Endpoint", data.at(0));
            }
            else if (data.size() == 2)
            {
                result.emplace(data.at(0), data.at(1));
            }
            else
            {
                // Do nothing.
                //
            }
        }
    }

    return result;
}


String::Vector String::split(const std::string& theString, const char delim)
{
    Vector result;

    constexpr size_t MAX_EXPECTED_SIZE = 2;
    result.reserve(MAX_EXPECTED_SIZE);

    const size_t index = theString.find_first_of(delim);

    if (index != std::string::npos)
    {
        constexpr size_t offset = 2;
        result.push_back(theString.substr(0, index));
        result.push_back(theString.substr(index + offset));
    }
    else
    {
        result.push_back(theString);
    }

    return result;
}


std::string String::endPoint(const std::string& endPointString)
{
    constexpr size_t offset = 1;
    constexpr char delim = '/';
    const size_t firstIndex = endPointString.find_first_of(delim);
    const std::string subString = endPointString.substr(firstIndex + offset);

    constexpr char space = ' ';
    const size_t secondIndex = subString.find_first_of(space);

    return subString.substr(0, secondIndex);
}
