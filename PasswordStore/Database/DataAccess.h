#pragma once

#include <memory>
#include <pqxx/pqxx>


class DataAccess final
{
public:
    DataAccess(void);
    ~DataAccess(void);
    DataAccess(const DataAccess& RHS) = delete;
    DataAccess(DataAccess&& RHS) = delete;
    DataAccess& operator=(const DataAccess& RHS) = delete;
    DataAccess& operator=(DataAccess&& RHS) = delete;

private:
    std::unique_ptr<pqxx::connection> m_pqxx;
};
