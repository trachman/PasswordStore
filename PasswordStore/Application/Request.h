#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Commands.h"
#include "TransactionStatus.h"


class Request
{
public:
    Request(const std::string& theRequestString);
    ~Request(void) = default;
    Request(void) = delete;
    Request(const Request& RHS) = delete;
    Request(Request&& RHS) = delete;
    Request& operator=(const Request& RHS) = delete;
    Request& operator=(Request&& RHS) = delete;

    TransactionStatus dispatchCommand(void);

private:

    std::unique_ptr<Command> m_command;
};
