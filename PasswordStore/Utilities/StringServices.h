#pragma once

#include <string>
#include <unordered_map>
#include <vector>


using Data = std::unordered_map<std::string, std::string>;


namespace String
{
    // Using Declarations
    //
    using Vector = std::vector<std::string>;

    // Command String Constants
    //
    static const std::string ENDPOINT                = "Endpoint";
    static const std::string CREATE_NEW_ACCOUNT      = "CreateNewAccount";
    static const std::string LOGIN                   = "Login";
    static const std::string ADD_NEW_SERVICE         = "AddNewService";
    static const std::string DELETE_EXISTING_SERVICE = "DeleteExistingService";
    static const std::string COPY_SERVICE_USERNAME   = "CopyServiceUsername";
    static const std::string COPY_SERVICE_PASSWORD   = "CopyServicePassword";
    static const std::string DELETE_ACCOUNT          = "DeleteAccount";
    static const std::string LOGOUT                  = "Logout";

    // Data String Constants
    //
    static const std::string USERNAME            = "Username";
    static const std::string PASSWORD            = "Password";
    static const std::string SESSION_ID          = "SessionId";
    static const std::string SERVICE_NAME        = "ServiceName";
    static const std::string SERVICE_USERNAME    = "ServiceUsername";
    static const std::string SERVICE_PASSWORD    = "ServicePassword";
    static const std::string SERVICE_URL         = "ServiceURL";
    static const std::string SERVICE_DESCRIPTION = "ServiceDescription";
    static const std::string EMPTY_STRING        = "";

    // Database Constants
    //
    static const std::string DB_USER     = "user";
    static const std::string DB_HOST     = "host";
    static const std::string DB_PORT     = "port";
    static const std::string DB_PASSWORD = "password";
    static const std::string DB_NAME     = "dbname";

    // Helper Methods
    //
    Data explodeRequest(const std::string& theString);
    Vector split(
        const std::string& theString,
        const char delim,
        const size_t offset);
    std::string endPoint(const std::string& endPointString);
    std::string dbConnectionString(void);
}; 