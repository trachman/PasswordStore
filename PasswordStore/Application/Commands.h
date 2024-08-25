#pragma once

#include <string>
#include <unordered_map>


enum class Command
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


const std::unordered_map<std::string, Command> EndPointToCommand =
{
    // Commands when a user is not logged in
    //
    {"CreateNewAccount", Command::CREATE_NEW_ACCOUNT},
    {"Login", Command::LOGIN},

    // Commands when a user is logged in
    //
    {"AddNewService", Command::ADD_NEW_SERVICE},
    {"DeleteExistingService", Command::DELETE_EXISTING_SERVICE},
    {"CopyServiceUsername", Command::COPY_SERVICE_USERNAME},
    {"CopyServicePassword", Command::COPY_SERVICE_PASSWORD},
    {"DeleteAccount", Command::DELETE_ACCOUNT},
    {"Logout", Command::LOGOUT}
};
