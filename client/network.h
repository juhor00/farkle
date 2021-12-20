#ifndef NETWORK_H
#define NETWORK_H

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


class Network
{
public:
    Network(const std::string serverName, const std::string port);
    ~Network();
    bool sendToServer(const std::string& sendbuf);
    void receive();

private:

    SOCKET ConnectSocket = INVALID_SOCKET;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    std::thread* recv_thread;
};

#endif // NETWORK_H
