#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "utilities.h"
#include <winsock2.h>

using command = std::string;
using parameters = std::vector<std::string>;
using message = std::string;

class Event
{
public:
    Event(message message);
    Event(message message, SOCKET client);
    command getCommand();
    parameters getParameters();
    SOCKET getClient();
    void print();

private:

    command command;
    parameters parameters;
    SOCKET client;
};

#endif // EVENT_H
