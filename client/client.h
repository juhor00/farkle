#ifndef CLIENT_H
#define CLIENT_H

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

struct addrinfo;

class Event;

class Client
{
public:
    Client();
    virtual ~Client();
    bool isConnected();
    bool sendToServer(const std::string& sendbuf);
    void receive();

protected:
    virtual void noConnectionEvent() = 0;
    virtual bool handleEvent(Event& event) = 0;

private:

    SOCKET ConnectSocket_ = INVALID_SOCKET;
    char recvbuf_[DEFAULT_BUFLEN];
    int recvbuflen_ = DEFAULT_BUFLEN;
    std::thread* recvThread_;
};

#endif // CLIENT_H
