#include "DataAccess.h"

#include <vector>
#include <string>
#include "StringServices.h"


namespace
{
    using Row  = std::vector<std::string>;
    using Rows = std::vector<Row>;


    Rows mapResultToDbRows(const pqxx::result& dbResult)
    {
        Rows dbRows;

        for (auto const& row : dbResult)
        {
            Row dbRow;

            for (auto const& field : row)
            {
                dbRow.emplace_back(field.c_str());
            }

            dbRows.emplace_back(std::move(dbRow));
        }

        return dbRows;
    }
}


DataAccess::DataAccess(void)
: m_pqxx(std::make_unique<pqxx::connection>(
    String::dbConnectionString()))
{
}


DataAccess::~DataAccess(void)
{
    m_pqxx.reset();
}


TransactionStatus::State DataAccess::addNewAccount(
    const std::string& username,
    const std::string& password,
    std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    const std::string sql =
        "INSERT INTO \"Accounts\" "
        "VALUES ('" +
        username +
        "','" +
        password +
        "')";

    try
    {
        pqxx::work w(*m_pqxx);
        pqxx::result dbResult = w.exec(sql);
        w.commit();

        theResult = State::PASS;
    }
    catch (std::exception& e)
    {
        errorMessage = e.what();

        theResult = State::FAIL;
    }

    return theResult;
}
