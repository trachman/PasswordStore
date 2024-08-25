#pragma once

#include <unordered_map>
#include <string>
#include "Commands.h"


class Request
{
public:
    Request(const std::string& theRequestString);

    ~Request(void) = default;

    Command viewCommand(void) const;

    Request(void) = delete;
    Request(const Request& RHS) = delete;
    Request(Request&& RHS) = delete;
    Request& operator=(const Request& RHS) = delete;
    Request& operator=(Request&& RHS) = delete;

private:
    using Data = std::unordered_map<std::string, std::string>;

    void parse(const std::string& theRequestString);

    Command m_command;
    Data m_data;
};
