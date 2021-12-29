#ifndef SERVER_H
#define SERVER_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

struct addrinfo;

class EventHandler;

class Server
{
public:
    Server(EventHandler* eventHandler, const std::string serverName, const std::string port);
    ~Server();
    bool isConnected();
    bool sendToServer(const std::string& sendbuf);
    void receive();

private:

    EventHandler* eventHandler_;
    SOCKET ConnectSocket_ = INVALID_SOCKET;
    char recvbuf_[DEFAULT_BUFLEN];
    int recvbuflen_ = DEFAULT_BUFLEN;
    std::thread* recvThread_;
};

#endif // SERVER_H
