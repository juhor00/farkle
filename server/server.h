#ifndef SERVER_H
#define SERVER_H

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <thread>
#include <string>

#include "../event.h"
#include "eventhandler.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512

class EventHandler;

class Server
{
public:
    Server(const std::string& port = "27015");
    ~Server();
    void linkEventHandler(EventHandler* e);

    bool sendToClient(SOCKET& client, const std::string& msg);
    bool broadcast(const std::string& msg);

private:

    bool addClient(SOCKET& client);
    bool removeClient(SOCKET& client);
    bool hasClient(SOCKET& client);

    void stopListen();
    void acceptClients();
    void handle(SOCKET& client);

    EventHandler* eventHandler;
    SOCKET ListenSocket = INVALID_SOCKET;
    std::unordered_set<SOCKET> ClientSockets;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
};

#endif // SERVER_H
