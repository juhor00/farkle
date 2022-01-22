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
#include <algorithm>

#include "../event.h"

#define DEFAULT_BUFLEN 512


class Server
{
public:
    Server(const std::string& port = "27015");
    virtual ~Server();

protected:

    bool sendToClient(SOCKET& client, const std::string& msg);
    bool broadcast(const std::string& msg);
    void acceptClients();

    virtual bool handleEvent(Event& event)=0;
    virtual bool addClient(SOCKET client);
    virtual bool removeClient(SOCKET client);

private:

    void closeConnection(SOCKET client);
    bool hasClient(SOCKET& client);

    void stopListen();
    void handle(SOCKET client);

    SOCKET ListenSocket = INVALID_SOCKET;
    std::unordered_set<SOCKET> ClientSockets;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
};

#endif // SERVER_H
