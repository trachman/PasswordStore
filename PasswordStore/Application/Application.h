#pragma once

#include <memory>

#include "Request.h"
#include "TransactionStatus.h"


class Application
{
public:
    static Application& instance(void);

    TransactionStatus dispatchCommand(const std::string& theRequestString);

private:
    static std::unique_ptr<Application> m_instance;
};
