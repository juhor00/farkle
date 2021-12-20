#include "network.h"

Network::Network(const char* serverName)
{
    WSADATA wsaData;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Unable to connect to server!" << std::endl;
        WSACleanup();
        return;
    }
    std::cout << "Connected to the server" << std::endl;
    std::thread t(&Network::receive, this);
    t.detach();

}

Network::~Network()
{
    // shutdown the connection since no more data will be sent
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
    }
    closesocket(ConnectSocket);
    WSACleanup();
}

bool Network::sendToServer(const std::string& sendbuf)
{
    const char *test = "this is a test";
    int result = send(ConnectSocket, test, (int)strlen(test), 0);
    if(result == SOCKET_ERROR){
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << result << " bytes sent" << std::endl;
    return true;
}

void Network::receive()
{
    int iResult;
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            std::cout << "Bytes received: " << iResult << std::endl;
        else if ( iResult == 0 )
            std::cout << "Connection closed" << std::endl;
        else
            std::cerr << "recv failed with error: " << WSAGetLastError();

    } while( iResult > 0 );
}
