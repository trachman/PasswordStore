#pragma once

// Includes
//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WIN32_WINNT 0x0501     // Tells Windows we are beyond Windows XP (rip)

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <vector>
#include "TransactionStatus.h"


// Server
// 
// Encapsulates the low level networking code required to run this application.
// Accepts HTTP requests and dispatches commands.
//
class Server
{
public:
    // Constructor
    // 
    // Description:
    // Creates the server object and initializes the members.
    // 
    // Arguments:
    // None.
    //
    Server(void);

    // Destructor
    // 
    // Description:
    // Destroys the server and cleans up all memory.
    // 
    // Arguments:
    // None.
    //
    ~Server(void);

    // Deleted special member functions.
    // 
    // The server shall not be copyable or moved.
    // This class is designed to be created once and then destroyed.
    //
    Server(const Server& RHS) = delete;
    Server(Server&& RHS) = delete;
    Server& operator=(const Server& RHS) = delete;
    Server& operator=(Server&& RHS) = delete;

    // run
    // 
    // Description:
    // The method that launches the server.
    // Does initialization and dispatches commands.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // EXIT_SUCCESS if run finishes successfully.
    // EXIT_FAILURE otherwise.
    //
    int run(void);

private:
    // initialize
    // 
    // Description:
    // Initializes Winsock.
    // Resolves server address and port.
    // Creates a socket.
    // Binds the socket.
    // Listens on the socket.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if initialization was successful.
    // False otherwise.
    //
    bool initialize(void);

    // initializeWinsock
    // 
    // Description:
    // Initializes Winsock.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool initializeWinsock(void);

    // resolveAddressAndPort
    // 
    // Description:
    // Resolves the address and port.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool resolveAddressAndPort(void);

    // createSocket
    // 
    // Description:
    // Creates a SOCKET for connecting to the server.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool createSocket(void);

    // bindSocket
    // 
    // Description:
    // Binds the TCP listening socket.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool bindSocket(void);

    // listenOnSocket
    // 
    // Description:
    // Sets up listening on the TCP listening socket.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool listenOnSocket(void);

    // acceptClientConnections
    // 
    // Description:
    // Main loop which accepts connections and dispatches commands.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if the loop does not fail.
    // False otherwise.
    //
    bool acceptClientConnections(void);

    // acceptClientSocket
    // 
    // Description:
    // Accepts a client socket.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool acceptClientSocket(void);

    // receiveClientSocketRequest
    // 
    // Description:
    // Receives a client socket request and dispatches a command.
    // 
    // Arguments:
    // recvBuffer - The client request text.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool receiveClientSocketRequest(std::vector<char>& recvBuffer);

    // closeClientSocket
    // 
    // Description:
    // Closes a client socket after request has been handled.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if successful.
    // False otherwise.
    //
    bool closeClientSocket(void);

    // dispatchCommand
    // 
    // Description:
    // Dispatches the command to the API layer.
    // 
    // Arguments:
    // recvBuffer - The received HTTP Request.
    // 
    // Returns:
    // Transaction Status with the result of the command.
    //
    TransactionStatus dispatchCommand(const std::vector<char>& recvBuffer) const;

    // sendResponseToClient
    // 
    // Description:
    // Sends a response to the client given the inputted transaction status.
    // 
    // Arguments:
    // transactionStatus - The response to send the client.
    // 
    // Returns:
    // None.
    //
    void sendResponseToClient(const TransactionStatus& transactionStatus);

    // Private Data Members
    //
    addrinfo* m_result;
    addrinfo m_hints;
    WSADATA m_wsaData;
    SOCKET m_listenSocket;
    SOCKET m_clientSocket;
    int m_iResult;
    int m_iSendResult;
};
