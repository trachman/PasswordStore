#include "Application.h"

#include "Commands.h"


Application& Application::instance(void)
{
    static std::unique_ptr<Application> m_instance;

    if (m_instance == nullptr)
    {
        m_instance = std::make_unique<Application>();
    }

    return *m_instance;
}


TransactionStatus Application::dispatchCommand(const std::string& theRequestString)
{
    Request theRequest(theRequestString);

    return theRequest.dispatchCommand();
}
