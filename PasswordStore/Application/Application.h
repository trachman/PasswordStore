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
    // TODO
    // Make these derived classes from a class called Command
    //
    TransactionStatus createNewAccount(const Request& theRequest);
    TransactionStatus login(const Request& theRequest);
    TransactionStatus addNewService(const Request& theRequest);
    TransactionStatus deleteExistingService(const Request& theRequest);
    TransactionStatus copyServiceUsername(const Request& theRequest);
    TransactionStatus copyServicePassword(const Request& theRequest);
    TransactionStatus deleteAccount(const Request& theRequest);
    TransactionStatus logout(const Request& theRequest);

    static std::unique_ptr<Application> m_instance;
};
