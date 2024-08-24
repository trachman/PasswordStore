// Includes
//
#include "Server.h"

#include <iostream>


// Anonymous Namespace
// 
// Description:
// Contains constants used throughout this basic server.
//
namespace
{
    constexpr PCSTR DEFAULT_PORT = "27015";
    constexpr size_t DEFAULT_BUFLEN = 2048;
}


// Constructor
// 
// Description:
// Creates the server object and initializes the members.
//
Server::Server(void)
: m_result(nullptr),
  m_hints{},
  m_wsaData{},
  m_listenSocket(INVALID_SOCKET),
  m_clientSocket(INVALID_SOCKET),
  m_iResult(SOCKET_ERROR),
  m_iSendResult(SOCKET_ERROR)
{
    // Nothing else to do.
    //
}


// Destructor
// 
// Description:
// Destroys the server and cleans up all memory.
//
Server::~Server(void)
{
    freeaddrinfo(m_result);
    closesocket(m_listenSocket);
    closesocket(m_clientSocket);
    WSACleanup();

    m_result = nullptr;
    m_hints = {};
    m_wsaData = {};
    m_listenSocket = INVALID_SOCKET;
    m_clientSocket = INVALID_SOCKET;
    m_iResult = SOCKET_ERROR;
    m_iSendResult = SOCKET_ERROR;
}


// run
// 
// Description:
// The method that launches the server.
// Does initialization and dispatches commands.
// 
int Server::run(void)
{
    bool theResult = true;

    theResult = theResult && this->initialize();
    theResult = theResult && this->acceptClientConnections();

    return theResult ? EXIT_SUCCESS : EXIT_FAILURE;
}


// initialize
// 
// Description:
// Initializes Winsock.
// Resolves server address and port.
// Creates a socket.
// Binds the socket.
// Listens on the socket.
// 
bool Server::initialize(void)
{
    bool theResult = true;

    theResult = theResult && this->initializeWinsock();
    theResult = theResult && this->resolveAddressAndPort();
    theResult = theResult && this->createSocket();
    theResult = theResult && this->bindSocket();
    theResult = theResult && this->listenOnSocket();

    return theResult;
}


// initializeWinsock
// 
// Description:
// Initializes Winsock.
// 
bool Server::initializeWinsock(void)
{
    m_iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);

    const bool isSuccessful = m_iResult == 0;

    if (isSuccessful)
    {
        std::cout << "Winsock initialization successful." << std::endl;
    }
    else
    {
        std::cout << "WSAStartup failed with error: " << m_iResult << std::endl;
    }

    return isSuccessful;
}


// resolveAddressAndPort
// 
// Description:
// Resolves the address and port.
// 
bool Server::resolveAddressAndPort(void)
{
    ZeroMemory(&m_hints, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;
    m_hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    //
    m_iResult = getaddrinfo(nullptr, DEFAULT_PORT, &m_hints, &m_result);

    const bool isSuccessful = m_iResult == 0;

    if (isSuccessful)
    {
        std::cout << "Resolving the address and port successful." << std::endl;
    }
    else
    {
        std::cout << "getaddrinfo failed with error: " << m_iResult << std::endl;
    }

    return isSuccessful;
}


// createSocket
// 
// Description:
// Creates a SOCKET for connecting to the server.
// 
bool Server::createSocket(void)
{
    m_listenSocket = socket(
        m_result->ai_family,
        m_result->ai_socktype,
        m_result->ai_protocol);

    const bool isSuccessful = m_listenSocket != INVALID_SOCKET;

    if(isSuccessful)
    {
        std::cout << "Socket creation successful." << std::endl;
    }
    else
    {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
    }

    return isSuccessful;
}


// bindSocket
// 
// Description:
// Binds the TCP listening socket.
// 
bool Server::bindSocket(void)
{
    m_iResult = bind(
        m_listenSocket,
        m_result->ai_addr,
        static_cast<int>(m_result->ai_addrlen));

    const bool isSuccessful = m_iResult != SOCKET_ERROR;

    if (isSuccessful)
    {
        std::cout << "Socket bind successful." << std::endl;
    }
    else
    {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
    }

    return isSuccessful;
}


// listenOnSocket
// 
// Description:
// Sets up listening on the TCP listening socket.
// 
bool Server::listenOnSocket(void)
{
    freeaddrinfo(m_result);

    m_iResult = listen(m_listenSocket, SOMAXCONN);

    const bool isSuccessful = m_iResult != SOCKET_ERROR;

    if (isSuccessful)
    {
        std::cout << "Socket listening successful." << std::endl;
    }
    else
    {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
    }

    return isSuccessful;
}


// acceptClientConnections
// 
// Description:
// Main loop which accepts connections and dispatches commands.
// 
bool Server::acceptClientConnections(void)
{
    bool theResult = true;

    std::vector<char> recvBuffer;
    recvBuffer.resize(DEFAULT_BUFLEN);

    while (theResult)
    {
        m_clientSocket = INVALID_SOCKET;

        theResult = theResult && this->acceptClientSocket();
        theResult = theResult && this->receiveClientSocketRequest(recvBuffer);
        theResult = theResult && this->closeClientSocket();
    }

    return theResult;
}


// acceptClientSocket
// 
// Description:
// Accepts a client socket.
// 
bool Server::acceptClientSocket(void)
{
    std::cout << "------------- LISTENING FOR NEW CONNECTIONS ------------" << std::endl;

    m_clientSocket = accept(m_listenSocket, nullptr, nullptr);

    const bool isSuccessful = m_clientSocket != INVALID_SOCKET;

    if (isSuccessful)
    {
        std::cout << "Accept client socket successful." << std::endl;
    }
    else
    {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
    }

    return isSuccessful;
}


// receiveClientSocketRequest
// 
// Description:
// Receives a client socket request and dispatches a command.
// 
bool Server::receiveClientSocketRequest(std::vector<char>& recvBuffer)
{
    bool isSuccessful = true;

    m_iResult = recv(m_clientSocket, recvBuffer.data(), recvBuffer.size(), 0);

    std::cout << "Receive Buffer: "
              << std::string(recvBuffer.begin(), recvBuffer.end())
              << std::endl;

    if (m_iResult > 0)
    {
        std::cout << "Bytes received: " << m_iResult << std::endl;

        this->dispatchCommand(recvBuffer);

        // TODO
        // m_iSendResult is the number of bytes sent to the client.
        // when we actually have enough infrastructure to send stuff
        // to the client we will implement this. For now, return 1.
        //
        m_iSendResult = 1;
        std::cout << "Bytes sent: " << m_iSendResult << std::endl;
    }
    else if (m_iResult == 0)
    {
        std::cout << "Connection closing..." << std::endl;
    }
    else
    {
        isSuccessful = false;
        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
    }

    return isSuccessful;
}


// closeClientSocket
// 
// Description:
// Closes a client socket after request has been handled.
// 
bool Server::closeClientSocket(void)
{
    // Close the ClientSocket after data has been sent
    //
    m_iResult = shutdown(m_clientSocket, SD_SEND);

    const bool isSuccessful = m_iResult != SOCKET_ERROR;

    if (isSuccessful)
    {
        std::cout << "Shutdown client socket successful." << std::endl;
    }
    else
    {
        std::cout << "shutdown failed with error: " << WSAGetLastError() << std::endl;
    }

    std::cout << "------------- CONNECTION CLOSED ------------------------" << std::endl;

    return isSuccessful;
}


// dispatchCommand
// 
// Description:
// Dispatches the command to the API layer.
// 
TransactionStatus Server::dispatchCommand(const std::vector<char>& recvBuffer) const
{
    const std::string request(recvBuffer.begin(), recvBuffer.end());

    // TODO
    // Pass request string to API Layer which will dispatch a command to
    // the application.
    //

    return TransactionStatus();
}
