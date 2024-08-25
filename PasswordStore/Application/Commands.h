#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "TransactionStatus.h"


using Data = std::unordered_map<std::string, std::string>;


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

protected:
    const Data& m_inputData;
    Data m_outputData;
    TransactionStatus m_transactionStatus;

private:
    void openConnection(void);
    void closeConnection(void);
    virtual void do_processCommand(void) = 0;
};


class CreateNewAccountCommand : public Command
{
public:
    CreateNewAccountCommand(const Data& data);
    CreateNewAccountCommand(void) = delete;
private:
    void do_processCommand(void) override;

    static constexpr CommandType m_type = CommandType::CREATE_NEW_ACCOUNT;
};


class LoginCommand : public Command
{
public:
    LoginCommand(const Data& data);
    LoginCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::LOGIN;
};


class AddNewServiceCommand : public Command
{
public:
    AddNewServiceCommand(const Data& data);
    AddNewServiceCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::ADD_NEW_SERVICE;
};


class DeleteExistingServiceCommand : public Command
{
public:
    DeleteExistingServiceCommand(const Data& data);
    DeleteExistingServiceCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::DELETE_EXISTING_SERVICE;
};


class CopyServiceUsernameCommand : public Command
{
public:
    CopyServiceUsernameCommand(const Data& data);
    CopyServiceUsernameCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::COPY_SERVICE_USERNAME;
};


class CopyServicePasswordCommand : public Command
{
public:
    CopyServicePasswordCommand(const Data& data);
    CopyServicePasswordCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::COPY_SERVICE_PASSWORD;
};


class DeleteAccountCommand : public Command
{
public:
    DeleteAccountCommand(const Data& data);
    DeleteAccountCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::DELETE_ACCOUNT;
};


class LogoutCommand : public Command
{
public:
    LogoutCommand(const Data& data);
    LogoutCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::LOGOUT;
};


class BlankCommand : public Command
{
public:
    BlankCommand(const Data& data);
    BlankCommand(void) = delete;
private:
    void do_processCommand(void) override;
    static constexpr CommandType m_type = CommandType::UNDEFINED;
};


namespace Commands
{
    std::unique_ptr<Command> createNew(const Data& fromTheData);
};

