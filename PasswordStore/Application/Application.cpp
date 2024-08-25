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
    TransactionStatus theResult;

    Request theRequest(theRequestString);

    switch (theRequest.viewCommand())
    {
        case Command::CREATE_NEW_ACCOUNT:
        {
            theResult = this->createNewAccount(theRequest);
            break;
        }
        case Command::LOGIN:
        {
            theResult = this->login(theRequest);
            break;
        }
        case Command::ADD_NEW_SERVICE:
        {
            theResult = this->addNewService(theRequest);
            break;
        }
        case Command::DELETE_EXISTING_SERVICE:
        {
            theResult = this->deleteExistingService(theRequest);
            break;
        }
        case Command::COPY_SERVICE_USERNAME:
        {
            theResult = this->copyServiceUsername(theRequest);
            break;
        }
        case Command::COPY_SERVICE_PASSWORD:
        {
            theResult = this->copyServicePassword(theRequest);
            break;
        }
        case Command::DELETE_ACCOUNT:
        {
            theResult = this->deleteAccount(theRequest);
            break;
        }
        case Command::LOGOUT:
        {
            theResult = this->logout(theRequest);
            break;
        }
        case Command::UNDEFINED:
        {
            // Do nothing.
            // Unrecognized request.
            //
            break;
        }
        default:
        {
            // Assert.
            // A Command enum has been added without adding a case to this method.
            //
            static_assert(true, "Unknown command type");
        }
    }

    return theResult;
}


TransactionStatus Application::createNewAccount(const Request& theRequest)
{
    // TODO
    // Add new username and password to the Account table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::login(const Request& theRequest)
{
    // TODO
    // Add new entry for the user in the Session table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::addNewService(const Request& theRequest)
{
    // TODO
    // Add new service to the Service table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::deleteExistingService(const Request& theRequest)
{
    // TODO
    // Delete existing service from the Service table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::copyServiceUsername(const Request& theRequest)
{
    // TODO
    // Copy service username from the Service table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::copyServicePassword(const Request& theRequest)
{
    // TODO
    // Copy service password from the Service table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::deleteAccount(const Request& theRequest)
{
    // TODO
    // Delete account from the Account table in the database
    //
    return TransactionStatus();
}


TransactionStatus Application::logout(const Request& theRequest)
{
    // TODO
    // Remove entry from the logged in user from the Session table in the database
    //
    return TransactionStatus();
}
