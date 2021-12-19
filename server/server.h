#ifndef SERVER_H
#define SERVER_H

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <memory>
#include <thread>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"



class Server
{
public:
    Server();
    ~Server();


private:

    void acceptClients();

    static void handle(SOCKET& client);

    SOCKET ListenSocket = INVALID_SOCKET;
    std::vector<SOCKET> ClientSockets;
};

#endif // SERVER_H
