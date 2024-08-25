#pragma once

#include <string>
#include <unordered_map>
#include <vector>


namespace String
{
    // Using Declarations
    //
    using Vector = std::vector<std::string>;

    // Command String Constants
    //
    static const std::string ENDPOINT =                "Endpoint";
    static const std::string CREATE_NEW_ACCOUNT =      "CreateNewAccount";
    static const std::string LOGIN =                   "Login";
    static const std::string ADD_NEW_SERVICE =         "AddNewService";
    static const std::string DELETE_EXISTING_SERVICE = "DeleteExistingService";
    static const std::string COPY_SERVICE_USERNAME =   "CopyServiceUsername";
    static const std::string COPY_SERVICE_PASSWORD =   "CopyServicePassword";
    static const std::string DELETE_ACCOUNT =          "DeleteAccount";
    static const std::string LOGOUT =                  "Logout";

    // Data String Constants
    //
    static const std::string USERNAME = "Username";
    static const std::string PASSWORD = "Password";

    // Helper Methods
    //
    std::unordered_map<std::string, std::string> explodeRequest(
        const std::string& theString);

    Vector split(const std::string& theString, const char delim);

    std::string endPoint(const std::string& endPointString);
}; 