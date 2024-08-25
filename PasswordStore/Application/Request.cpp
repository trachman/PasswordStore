#include "Request.h"

#include "StringServices.h"


Request::Request(const std::string& theRequestString)
{
    m_command = Commands::createNew(String::explodeRequest(theRequestString));
}


TransactionStatus Request::dispatchCommand(void)
{
    if (m_command == nullptr)
    {
        return TransactionStatus();
    }

    return m_command->processCommand();
}
