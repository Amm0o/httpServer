// http client that sends a GET request to a server and prints the response
//
// Compile with: g++ -o simpleHTTPClient simpleHTTPClient.cpp -lws2_32
//
// Run with: simpleHTTPClient.exe
//
// Note: This code is adapted from the MSDN article "Winsock Client
// Example" at http://msdn.microsoft.com/en-us/library/windows/desktop/ms737591(v=vs.85).aspx


#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


int main () {
    // Initialize the winsocket

    WSADATA wsaDATA;

    WORD wVersionRequested = MAKEWORD(2,2);
    int result = WSAStartup(wVersionRequested, &wsaDATA);
    if (result != 0) {
        printf("Error while initializing winsocket: %d", result);
        return 1;
    }

    printf("Winsocket has been initialized \n");


    // Crete the socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error while creating the socket: " + clientSocket);
        return 2;
    }

    // Bind the socket
    struct sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(3001);
    clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clientSocket, (SOCKADDR*)(&clientAddress), sizeof(clientAddress)) != 0) {
        printf("Error while connecting to the server: %d", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 3;
    }

    printf("Connected to the server \n");

    

    // Connect to the server
    const char* headers = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    send(clientSocket, headers, strlen(headers), 0);

    // Receive the response
    char buffer[10000];
    memset(buffer, 0, sizeof(buffer));

    int size = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
    if (size > 0) {
        printf("Received response from the server: %s\n", buffer);
    } else {
        printf("Error while receiving the response: %d", WSAGetLastError());
    }

    // Cleanup the winsocket
    closesocket(clientSocket);
    WSACleanup();

    return 0;

}