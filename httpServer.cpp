#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// mingw32-make.exe  to make --> Not Working
// g++ .\httpServer.cpp -o server.exe -lws2_32 --> Working

int main()
{
    // Initialize the winsocket

    WSADATA wsaDATA;

    WORD wVersionRequested = MAKEWORD(2, 2);
    int result = WSAStartup(wVersionRequested, &wsaDATA);
    if (result != 0)
    {
        printf("Error while initializing winsocket: %d", result);
        return 1;
    }

    printf("Winsocket has been initialized \n");

    // Creating a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        printf("Error while creating the socket: " + serverSocket);
        return 2;
    }

    // TODO: CREATE AN OUTPUT FOR THE SOCKET VALUE
    printf("Socket has been created STATUS: %d\n", serverSocket);

    // Bind the scoket
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(3000);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.0");


    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Error while binding the socket: %d", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 3;
    }


    // Listen for connections
    if (listen(serverSocket, 10) == SOCKET_ERROR) {
        printf("Error while listening for connections: %d", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 4;
    }

    // Cleanup the winsocket
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}