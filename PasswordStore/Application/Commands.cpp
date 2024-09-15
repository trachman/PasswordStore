#include "Commands.h"


// TODO
// 1. Encryption for passwords
//

namespace
{
    static const std::unordered_map<std::string, CommandType> EndPointToCommand =
    {
        {String::CREATE_NEW_ACCOUNT,        CommandType::CREATE_NEW_ACCOUNT},
        {String::LOGIN,                     CommandType::LOGIN},
        {String::ADD_NEW_SERVICE,           CommandType::ADD_NEW_SERVICE},
        {String::DELETE_EXISTING_SERVICE,   CommandType::DELETE_EXISTING_SERVICE},
        {String::COPY_SERVICE_USERNAME,     CommandType::COPY_SERVICE_USERNAME},
        {String::COPY_SERVICE_PASSWORD,     CommandType::COPY_SERVICE_PASSWORD},
        {String::DELETE_ACCOUNT,            CommandType::DELETE_ACCOUNT},
        {String::LOGOUT,                    CommandType::LOGOUT}
    };
}


Command::Command(const Data& inputData)
: m_inputData(inputData),
  m_outputData{},
  m_transactionStatus(TransactionStatus())
{
    m_transactionStatus.setState(TransactionStatus::State::IN_PROGRESS);
}


TransactionStatus Command::processCommand(void)
{
    if (!this->validateData())
    {
        m_transactionStatus.setErrorMessage("Invalid data.");
        m_transactionStatus.setState(TransactionStatus::State::FAIL);
        return m_transactionStatus;
    }

    this->openConnection();

    this->do_processCommand();

    this->closeConnection();

    return m_transactionStatus;
}


std::string Command::viewInputDataValue(const std::string& key)
{
    if (!m_inputData.count(key))
    {
        return String::EMPTY_STRING;
    }

    return m_inputData.at(key);
}


void Command::openConnection(void)
{
    m_dataAccess.emplace();
}


void Command::closeConnection(void)
{
    m_dataAccess.reset();
}


CreateNewAccountCommand::CreateNewAccountCommand(const Data& data)
: Command(data)
{
    m_username = this->viewInputDataValue(String::USERNAME);
    m_password = this->viewInputDataValue(String::PASSWORD);
}


void CreateNewAccountCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->createNewAccount(
        m_username,
        m_password,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool CreateNewAccountCommand::validateData(void)
{
    return !m_username.empty() && !m_password.empty();
}


LoginCommand::LoginCommand(const Data& data)
: Command(data)
{
    m_username = this->viewInputDataValue(String::USERNAME);
    m_password = this->viewInputDataValue(String::PASSWORD);
}


void LoginCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->login(
        m_username,
        m_password,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool LoginCommand::validateData(void)
{
    return !m_username.empty() && !m_password.empty();
}


AddNewServiceCommand::AddNewServiceCommand(const Data& data)
: Command(data)
{
    m_serviceName        = this->viewInputDataValue(String::SERVICE_NAME);
    m_serviceUsername    = this->viewInputDataValue(String::SERVICE_USERNAME);
    m_servicePassword    = this->viewInputDataValue(String::SERVICE_PASSWORD);
    m_serviceURL         = this->viewInputDataValue(String::SERVICE_URL);
    m_serviceDescription = this->viewInputDataValue(String::SERVICE_DESCRIPTION);
    m_username           = this->viewInputDataValue(String::USERNAME);
    m_sessionId          = this->viewInputDataValue(String::SESSION_ID);
}


void AddNewServiceCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->addNewService(
        m_serviceName,
        m_serviceUsername,
        m_servicePassword,
        m_serviceURL,
        m_serviceDescription,
        m_username,
        m_sessionId,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool AddNewServiceCommand::validateData(void)
{
    return !m_serviceName.empty() && !m_serviceUsername.empty()
        && !m_servicePassword.empty() && !m_username.empty()
        && !m_sessionId.empty();
}


DeleteExistingServiceCommand::DeleteExistingServiceCommand(const Data& data)
: Command(data)
{
    m_serviceName = this->viewInputDataValue(String::SERVICE_NAME);
    m_username    = this->viewInputDataValue(String::USERNAME);
    m_sessionId   = this->viewInputDataValue(String::SESSION_ID);
}


void DeleteExistingServiceCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->deleteExistingService(
        m_serviceName,
        m_username,
        m_sessionId,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool DeleteExistingServiceCommand::validateData(void)
{
    return !m_serviceName.empty() && !m_username.empty() && !m_sessionId.empty();
}


CopyServiceUsernameCommand::CopyServiceUsernameCommand(const Data& data)
: Command(data)
{
    m_serviceName = this->viewInputDataValue(String::SERVICE_NAME);
    m_username    = this->viewInputDataValue(String::USERNAME);
    m_sessionId   = this->viewInputDataValue(String::SESSION_ID);
}


void CopyServiceUsernameCommand::do_processCommand(void)
{
    // TODO
    //
    m_transactionStatus.setState(TransactionStatus::State::PASS);
}


bool CopyServiceUsernameCommand::validateData(void)
{
    return !m_serviceName.empty() && !m_username.empty() && !m_sessionId.empty();
}


CopyServicePasswordCommand::CopyServicePasswordCommand(const Data& data)
: Command(data)
{
    m_serviceName = this->viewInputDataValue(String::SERVICE_NAME);
    m_username    = this->viewInputDataValue(String::USERNAME);
    m_sessionId   = this->viewInputDataValue(String::SESSION_ID);
}


void CopyServicePasswordCommand::do_processCommand(void)
{
    // TODO
    //
    m_transactionStatus.setState(TransactionStatus::State::PASS);
}


bool CopyServicePasswordCommand::validateData(void)
{
    return !m_serviceName.empty() && !m_username.empty() && !m_sessionId.empty();
}


DeleteAccountCommand::DeleteAccountCommand(const Data& data)
: Command(data)
{
    m_username  = this->viewInputDataValue(String::USERNAME);
    m_sessionId = this->viewInputDataValue(String::SESSION_ID);
}


void DeleteAccountCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->deleteAccount(
        m_username,
        m_sessionId,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool DeleteAccountCommand::validateData(void)
{
    return !m_username.empty() && !m_sessionId.empty();
}


LogoutCommand::LogoutCommand(const Data& data)
: Command(data)
{
    m_username  = this->viewInputDataValue(String::USERNAME);
    m_sessionId = this->viewInputDataValue(String::SESSION_ID);
}


void LogoutCommand::do_processCommand(void)
{
    using State = TransactionStatus::State;

    std::string errorMessage;
    const State result = m_dataAccess->logout(
        m_username,
        m_sessionId,
        errorMessage);

    m_transactionStatus.setState(result);
    m_transactionStatus.setErrorMessage(errorMessage);
}


bool LogoutCommand::validateData(void)
{
    return !m_username.empty() && !m_sessionId.empty();
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
        return nullptr;
    }

    return nullptr;
}
