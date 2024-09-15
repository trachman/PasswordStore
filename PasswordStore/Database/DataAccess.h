#pragma once

#include <memory>
#include <string>
#include <pqxx/pqxx>
#include "TransactionStatus.h"


class DataAccess final
{
public:
    DataAccess(void);
    ~DataAccess(void);
    DataAccess(const DataAccess& RHS) = delete;
    DataAccess(DataAccess&& RHS) = delete;
    DataAccess& operator=(const DataAccess& RHS) = delete;
    DataAccess& operator=(DataAccess&& RHS) = delete;

    // DATABASE COMMANDS
    TransactionStatus::State createNewAccount(
        const std::string& username,
        const std::string& password,
        std::string& errorMessage);
    TransactionStatus::State login(
        const std::string& username,
        const std::string& password,
        std::string& errorMessage);
    TransactionStatus::State logout(
        const std::string& username,
        const std::string& sessionId,
        std::string& errorMessage);
    TransactionStatus::State deleteAccount(
        const std::string& username,
        const std::string& sessionId,
        std::string& errorMessage);
    TransactionStatus::State addNewService(
        const std::string& serviceName,
        const std::string& serviceUsername,
        const std::string& servicePassword,
        const std::string& serviceURL,
        const std::string& serviceDescription,
        const std::string& username,
        const std::string& sessionId,
        std::string& errorMessage);
    TransactionStatus::State deleteExistingService(
        const std::string& serviceName,
        const std::string& username,
        const std::string& sessionId,
        std::string& errorMessage);

private:
    bool isLoggedIn(const std::string& username, const std::string& sessionId);

    std::unique_ptr<pqxx::connection> m_pqxx;
};
