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


TransactionStatus::State DataAccess::createNewAccount(
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


TransactionStatus::State DataAccess::login(
    const std::string& username,
    const std::string& password,
    std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    // 1. Validate the user
    // 2. Add user to the session table
    // 
    const std::string validateSql =
        "SELECT * FROM \"Accounts\" "
        "WHERE (\"Username\"='" +
        username +
        "')";

    const std::string sessionSql =
        "INSERT INTO \"Session\" "
        "VALUES ('" +
        username +
        "','" +
        "0123456789" + // Fake session id for now. UUID generation TODO.
        "')";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result validateResult = w.exec(validateSql);
        Rows accountData = mapResultToDbRows(validateResult);

        if (accountData.empty())
        {
            errorMessage = "Unknown username.";
            theResult = State::FAIL;
            return theResult;
        }

        const std::string storedPassword = accountData.front().at(1);

        if (password != storedPassword)
        {
            errorMessage = "Incorrect password.";
            theResult = State::FAIL;
            return theResult;
        }

        pqxx::result sessionResult = w.exec(sessionSql);
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
