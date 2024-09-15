#include "DataAccess.h"

#include <vector>
#include <string>
#include "StringServices.h"


// TODO
// 1. Data Sanitization to avoid SQL injection.
// 2. Create a base class for commands that need to check if
//    we are logged in or not before executing them.
// 3. UUID generation.
//

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


TransactionStatus::State DataAccess::logout(const std::string& username, const std::string& sessionId, std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    if (!this->isLoggedIn(username, sessionId))
    {
        errorMessage = "Requested account is not logged in.";
        theResult = State::FAIL;
        return theResult;
    }

    const std::string sql =
        "DELETE FROM \"Session\" "
        "WHERE \"Username\"='" +
        username +
        "'";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result result = w.exec(sql);
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


TransactionStatus::State DataAccess::deleteAccount(
    const std::string& username,
    const std::string& sessionId,
    std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    if (!this->isLoggedIn(username, sessionId))
    {
        errorMessage = "Requested account is not logged in.";
        theResult = State::FAIL;
        return theResult;
    }

    const std::string accountsSql =
        "DELETE FROM \"Accounts\" "
        "WHERE \"Username\"='" +
        username +
        "'";
    const std::string servicesSql =
        "DELETE FROM \"Services\" "
        "WHERE \"Username\"='" +
        username +
        "'";
    const std::string sessionSql =
        "DELETE FROM \"Session\" "
        "WHERE \"Username\"='" +
        username +
        "'";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result accountsResult = w.exec(accountsSql);
        pqxx::result servicesResult = w.exec(servicesSql);
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


TransactionStatus::State DataAccess::addNewService(
    const std::string& serviceName,
    const std::string& serviceUsername,
    const std::string& servicePassword,
    const std::string& serviceURL,
    const std::string& serviceDescription,
    const std::string& username,
    const std::string& sessionId,
    std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    if (!this->isLoggedIn(username, sessionId))
    {
        errorMessage = "Requested account is not logged in.";
        theResult = State::FAIL;
        return theResult;
    }

    const std::string servicesSql =
        "INSERT INTO \"Services\" "
        "VALUES ('" +
        serviceName +
        "','" +
        serviceUsername +
        "','" +
        servicePassword +
        "','" +
        serviceURL +
        "','" +
        serviceDescription +
        "','" +
        username +
        "')";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result servicesResult = w.exec(servicesSql);
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


TransactionStatus::State DataAccess::deleteExistingService(const std::string& serviceName, const std::string& username, const std::string& sessionId, std::string& errorMessage)
{
    using State = TransactionStatus::State;
    State theResult = State::IN_PROGRESS;

    if (!this->isLoggedIn(username, sessionId))
    {
        errorMessage = "Requested account is not logged in.";
        theResult = State::FAIL;
        return theResult;
    }

    const std::string servicesSql =
        "DELETE FROM \"Services\" "
        "WHERE \"Service Name\"='" +
        serviceName +
        "' AND \"Username\"='" +
        username +
        "'";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result servicesResult = w.exec(servicesSql);
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


bool DataAccess::isLoggedIn(const std::string& username, const std::string& sessionId)
{
    bool theResult = false;

    const std::string sql =
        "SELECT * FROM \"Session\" "
        "WHERE (\"Username\"='" +
        username +
        "' AND \"SessionId\"='" +
        sessionId +
        "')";

    try
    {
        pqxx::work w(*m_pqxx);

        pqxx::result result = w.exec(sql);
        Rows dbRows = mapResultToDbRows(result);
        w.commit();

        theResult = !dbRows.empty();
    }
    catch (std::exception& e)
    {
        theResult = false;
    }

    return theResult;
}
