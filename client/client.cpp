#include "client.h"
#include "eventhandler.h"

Client::Client()
{

    // Network settings
    std::string settingsFile = "networkConfig.txt";
    auto settings = utils::settingsParser(settingsFile);

    if(not utils::verifySettings(settings)){
        std::cerr << "File " << settingsFile << " is invalid" << std::endl;
        // INVALID NETWORK SETTINGS, DO SOMETHING
        return;
    }
    auto address = settings.at("ip-address");
    auto port = settings.at("port");


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
    iResult = getaddrinfo(&address[0], &port[0], &hints, &result);
    if ( iResult != 0 ) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket_ = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket_ == INVALID_SOCKET) {
            std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }
        // Connect to server.
        iResult = connect( ConnectSocket_, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket_);
            ConnectSocket_ = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    std::cout << "Connected to the server" << std::endl;
    recvThread_ = new std::thread(&Client::receive, this);
    sendToServer("HOLD 1 4 5");

}

Client::~Client()
{
    // shutdown the connection since no more data will be sent
    std::cout << "Closing connection to the server" << std::endl;
    int iResult = shutdown(ConnectSocket_, SD_BOTH);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
    } else {
        recvThread_->join();
        delete recvThread_;
    }
    closesocket(ConnectSocket_);
    WSACleanup();
}

bool Client::isConnected()
{
    return ConnectSocket_ != INVALID_SOCKET;
}

bool Client::sendToServer(const std::string& sendbuf)
{
    int result = send(ConnectSocket_, &sendbuf[0], (int) size(sendbuf), 0);
    if(result == SOCKET_ERROR){
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << result << " bytes sent" << std::endl;
    return true;
}

void Client::receive()
{
    int iResult;
    do {

        iResult = recv(ConnectSocket_, recvbuf_, recvbuflen_, 0);
        if ( iResult > 0 ){
            std::cout << "Bytes received: " << iResult << std::endl;
            message message(recvbuf_);
            message = message.substr(0, iResult);
            Event event(message);
            handleEvent(event);

        } else if ( iResult == 0 ){
            std::cout << "Connection closed" << std::endl;
        } else {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            ConnectSocket_ = INVALID_SOCKET;
            noConnectionEvent();
        }

    } while( iResult > 0 );
}
