#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Tell windows you are beyond windows xp
//
#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>


constexpr PCSTR DEFAULT_PORT = "27015";
constexpr size_t DEFAULT_BUFLEN = 512;
constexpr size_t MAX_LINE_LENGTH = 128;
constexpr size_t MAX_HTML_LENGTH = 1024;
constexpr size_t MAX_RESPONSE_LENGTH = 1200;


// Entry Point
//
int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    addrinfo* result = nullptr;
    addrinfo hints;
    int iResult = 0;
    int iSendResult = 0;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    //
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return EXIT_FAILURE;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    //
    iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }

    // Create a SOCKET for connecting to server
    //
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    //
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    // Main loop to handle server connections
    //
    while (true)
    {
        std::cout << "------------- LISTENING FOR NEW CONNECTIONS ------------" << std::endl;

        SOCKET ClientSocket = INVALID_SOCKET;

        // Accept a client socket
        //
        ClientSocket = accept(ListenSocket, nullptr, nullptr);
        if (ClientSocket == INVALID_SOCKET) {
            std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ListenSocket);
            WSACleanup();
            return EXIT_FAILURE;
        }

        // Receive client socket request
        //
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        std::cout << "Receive Buffer: " << recvbuf << std::endl;
        if (iResult > 0)
        {
            std::cout << "Bytes received: " << iResult << std::endl;

            std::cout << "WE GOT A CONNECTION!" << std::endl;

            // Number of bytes sent
            //
            iSendResult = 1;
            std::cout << "Bytes sent: " << iSendResult << std::endl;
        }
        else if (iResult == 0)
        {
            std::cout << "Connection closing..." << std::endl;
        }
        else
        {
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            WSACleanup();
            return EXIT_FAILURE;
        }

        // Close the ClientSocket after data has been sent
        //
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            std::cout << "shutdown failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            WSACleanup();
            return EXIT_FAILURE;
        }

        std::cout << "------------- CONNECTION CLOSED ------------------------" << std::endl;
    }

    // Cleanup
    //
    closesocket(ListenSocket);
    WSACleanup();

    return EXIT_SUCCESS;
}