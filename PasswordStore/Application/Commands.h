#pragma once

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>
#include "DataAccess.h"
#include "StringServices.h"
#include "TransactionStatus.h"


enum class CommandType
{
    UNDEFINED = -1,

    // Commands when a user is not logged in
    //
    CREATE_NEW_ACCOUNT,
    LOGIN,

    // Commands when a user is logged in
    //
    ADD_NEW_SERVICE,
    DELETE_EXISTING_SERVICE,
    COPY_SERVICE_USERNAME,
    COPY_SERVICE_PASSWORD,
    DELETE_ACCOUNT,
    LOGOUT
};


class Command
{
public:
    Command(const Data& inputData);
    virtual ~Command(void) = default;
    Command(void) = delete;
    Command(const Command& RHS) = delete;
    Command(Command&& RHS) = delete;
    Command& operator=(const Command& RHS) = delete;
    Command& operator=(Command&& RHS) = delete;

    TransactionStatus processCommand(void);
    virtual bool validateData(void) = 0;

protected:
    std::string viewInputDataValue(const std::string& key);

    Data m_outputData;
    TransactionStatus m_transactionStatus;
    std::optional<DataAccess> m_dataAccess;

private:
    void openConnection(void);
    void closeConnection(void);
    virtual void do_processCommand(void) = 0;

    Data m_inputData;
};


class CreateNewAccountCommand : public Command
{
public:
    CreateNewAccountCommand(const Data& data);
    CreateNewAccountCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;

    static constexpr CommandType m_type = CommandType::CREATE_NEW_ACCOUNT;
    std::string m_username;
    std::string m_password;
};


class LoginCommand : public Command
{
public:
    LoginCommand(const Data& data);
    LoginCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::LOGIN;
    std::string m_username;
    std::string m_password;
};


class AddNewServiceCommand : public Command
{
public:
    AddNewServiceCommand(const Data& data);
    AddNewServiceCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::ADD_NEW_SERVICE;
    std::string m_serviceName;
    std::string m_serviceUsername;
    std::string m_servicePassword;
    std::string m_serviceURL;
    std::string m_serviceDescription;
    std::string m_username;
    std::string m_sessionId;
};


class DeleteExistingServiceCommand : public Command
{
public:
    DeleteExistingServiceCommand(const Data& data);
    DeleteExistingServiceCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::DELETE_EXISTING_SERVICE;
    std::string m_serviceName;
    std::string m_username;
    std::string m_sessionId;
};


class CopyServiceUsernameCommand : public Command
{
public:
    CopyServiceUsernameCommand(const Data& data);
    CopyServiceUsernameCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::COPY_SERVICE_USERNAME;
    std::string m_serviceName;
    std::string m_username;
    std::string m_sessionId;
};


class CopyServicePasswordCommand : public Command
{
public:
    CopyServicePasswordCommand(const Data& data);
    CopyServicePasswordCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::COPY_SERVICE_PASSWORD;
    std::string m_serviceName;
    std::string m_username;
    std::string m_sessionId;
};


class DeleteAccountCommand : public Command
{
public:
    DeleteAccountCommand(const Data& data);
    DeleteAccountCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::DELETE_ACCOUNT;
    std::string m_username;
    std::string m_sessionId;
};


class LogoutCommand : public Command
{
public:
    LogoutCommand(const Data& data);
    LogoutCommand(void) = delete;
private:
    void do_processCommand(void) override;
    bool validateData(void) override;
    static constexpr CommandType m_type = CommandType::LOGOUT;
    std::string m_username;
    std::string m_sessionId;
};


namespace Commands
{
    std::unique_ptr<Command> createNew(const Data& fromTheData);
};

