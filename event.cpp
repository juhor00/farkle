#include "event.h"

Event::Event(message message):
    Event(INVALID_SOCKET, message){}

Event::Event(SOCKET client, message message):
    client(client)
{
    auto i = message.find(" ");
    command = message.substr(0, i);
    message.erase(0, i+1);
    parameters = utils::split(message);
}

std::string Event::getCommand()
{
    return command;
}

std::vector<std::string> Event::getParameters()
{
    return parameters;
}

SOCKET Event::getClient()
{
    return client;
}

void Event::print()
{
    std::cout << "EVENT INFO" << std::endl;

    std::cout << "Client: ";
    if(client!=INVALID_SOCKET){std::cout << client;} else {std::cout << "NULL";};
    std::cout << std::endl;

    std::cout << "Command: " << command << std::endl;
    std::cout << "Parameters: [ ";
    for(std::string& param : parameters){
        std::cout << param << " ";
    }
    std::cout << "]" << std::endl;
}
