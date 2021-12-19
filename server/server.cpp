#include "server.h"

Server::Server()
{
    WSADATA wsaData;
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    std::cout << "Server started successfully" << std::endl;
    acceptClients();
}

Server::~Server()
{
    // Close sockets
    closesocket(ListenSocket);
    for(SOCKET ClientSocket : ClientSockets){
        removeClient(ClientSocket);
    }
    WSACleanup();
}

bool Server::addClient(SOCKET &client)
{
    if(hasClient(client)){
        return false;
    }
    ClientSockets.insert(client);
    std::thread t(&handle, std::ref(client));
    t.detach();
    return true;
}

bool Server::removeClient(SOCKET &client)
{
    if(hasClient(client)){
        closesocket(client);
        ClientSockets.erase(client);
        return true;
    }
    return false;

}

bool Server::hasClient(SOCKET &client)
{
    return (std::find(ClientSockets.begin(), ClientSockets.end(), client) != ClientSockets.end());
}

void Server::acceptClients()
{
    while(true){
        std::cout << "Accepting new clients..." << std::endl;
        SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed with error: " << WSAGetLastError() << std::endl;
            return;
        } else {
            // New successful connection
            std::cout << "Added new client " << ClientSocket << std::endl;
            addClient(ClientSocket);
        }
    }
}

void Server::handle(SOCKET& client)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    while(true){
        std::cout << "Handling client " << client << std::endl;
        int msg = recv(client, recvbuf, recvbuflen, 0);
        if(msg > 0){
            std::cout << "Bytes received: " << msg << std::endl;
        } else if(msg == 0){
            std::cout << "Connection closing with " << client << std::endl;
        } else {
            std::cerr << "recv failed with error " << WSAGetLastError() << std::endl;
            closesocket(client);
            WSACleanup();
        }

    }
}
