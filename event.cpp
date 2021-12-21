#include "event.h"

Event::Event(std::string& message)
{
    auto i = message.find(" ");
    command = message.substr(0, i);
    message.erase(0, i+1);
    parameters = utils::split(message);
}

void Event::print()
{
    std::cout << "Command: " << command << std::endl;
    std::cout << "Parameters: [ ";
    for(std::string& param : parameters){
        std::cout << param << " ";
    }
    std::cout << "]" << std::endl;
}
