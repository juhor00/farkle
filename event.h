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
    Event(SOCKET client, message message);
    Event(SOCKET client, command cmd, parameters params);
    command getCommand();
    parameters getParameters();
    SOCKET getClient();
    void print();

private:

    SOCKET client_;
    command cmd_;
    parameters params_;
};

#endif // EVENT_H
