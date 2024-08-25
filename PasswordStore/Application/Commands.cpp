#include "Commands.h"

#include "StringServices.h"


namespace
{
    static const std::unordered_map<std::string, CommandType> EndPointToCommand =
    {
        // Commands when a user is not logged in
        //
        {"CreateNewAccount", CommandType::CREATE_NEW_ACCOUNT},
        {"Login", CommandType::LOGIN},

        // Commands when a user is logged in
        //
        {"AddNewService", CommandType::ADD_NEW_SERVICE},
        {"DeleteExistingService", CommandType::DELETE_EXISTING_SERVICE},
        {"CopyServiceUsername", CommandType::COPY_SERVICE_USERNAME},
        {"CopyServicePassword", CommandType::COPY_SERVICE_PASSWORD},
        {"DeleteAccount", CommandType::DELETE_ACCOUNT},
        {"Logout", CommandType::LOGOUT}
    };

}


Command::Command(const Data& inputData)
: m_inputData(inputData),
  m_outputData{},
  m_transactionStatus(TransactionStatus())
{
}


TransactionStatus Command::processCommand(void)
{
    this->openConnection();

    this->do_processCommand();

    this->closeConnection();

    return m_transactionStatus;
}


void Command::openConnection(void)
{
    // TODO
    // Database
    //
}


void Command::closeConnection(void)
{
    // TODO
    // Database
    //
}


CreateNewAccountCommand::CreateNewAccountCommand(const Data& data)
: Command(data)
{
}


void CreateNewAccountCommand::do_processCommand(void)
{
}


LoginCommand::LoginCommand(const Data& data)
: Command(data)
{
}


void LoginCommand::do_processCommand(void)
{
}


AddNewServiceCommand::AddNewServiceCommand(const Data& data)
: Command(data)
{
}


void AddNewServiceCommand::do_processCommand(void)
{
}


DeleteExistingServiceCommand::DeleteExistingServiceCommand(const Data& data)
: Command(data)
{
}


void DeleteExistingServiceCommand::do_processCommand(void)
{
}


CopyServiceUsernameCommand::CopyServiceUsernameCommand(const Data& data)
: Command(data)
{
}


void CopyServiceUsernameCommand::do_processCommand(void)
{
}


CopyServicePasswordCommand::CopyServicePasswordCommand(const Data& data)
: Command(data)
{
}


void CopyServicePasswordCommand::do_processCommand(void)
{
}


DeleteAccountCommand::DeleteAccountCommand(const Data& data)
: Command(data)
{
}


void DeleteAccountCommand::do_processCommand(void)
{
}


LogoutCommand::LogoutCommand(const Data& data)
: Command(data)
{
}


void LogoutCommand::do_processCommand(void)
{
}


BlankCommand::BlankCommand(const Data& data)
: Command(data)
{
}


void BlankCommand::do_processCommand(void)
{
}


std::unique_ptr<Command> Commands::createNew(const Data& fromTheData)
{
    const std::string endPoint = String::endPoint(fromTheData.at(String::ENDPOINT));

    const CommandType theCommandType = EndPointToCommand.count(endPoint) ?
        EndPointToCommand.at(endPoint) :
        CommandType::UNDEFINED;

    switch (theCommandType)
    {
    case CommandType::CREATE_NEW_ACCOUNT:
        return std::make_unique<CreateNewAccountCommand>(fromTheData);
    case CommandType::LOGIN:
        return std::make_unique<LoginCommand>(fromTheData);
    case CommandType::ADD_NEW_SERVICE:
        return std::make_unique<AddNewServiceCommand>(fromTheData);
    case CommandType::DELETE_EXISTING_SERVICE:
        return std::make_unique<DeleteExistingServiceCommand>(fromTheData);
    case CommandType::COPY_SERVICE_USERNAME:
        return std::make_unique<CopyServiceUsernameCommand>(fromTheData);
    case CommandType::COPY_SERVICE_PASSWORD:
        return std::make_unique<CopyServicePasswordCommand>(fromTheData);
    case CommandType::DELETE_ACCOUNT:
        return std::make_unique<DeleteAccountCommand>(fromTheData);
    case CommandType::LOGOUT:
        return std::make_unique<LogoutCommand>(fromTheData);
    case CommandType::UNDEFINED:
    default:
        return std::make_unique<BlankCommand>(fromTheData);
    }

    return std::make_unique<BlankCommand>(fromTheData);
}
