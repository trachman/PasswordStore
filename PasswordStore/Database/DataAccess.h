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

    TransactionStatus::State addNewAccount(
        const std::string& username,
        const std::string& password,
        std::string& errorMessage);

private:
    std::unique_ptr<pqxx::connection> m_pqxx;
};
