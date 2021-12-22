#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include "server.h"
#include <unordered_map>
#include <unordered_set>

using message = std::string;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&, SOCKET);
    typedef void (EventHandler::*generator)(parameters&, SOCKET);

    EventHandler(Server& server);

    bool generateEvent(Event& event);
    bool handleEvent(Event& event);

    // Handlers
    void holdEvent(parameters& params, SOCKET client);
    void saveEvent(parameters& params, SOCKET client);


private:

    bool isHandler(command& command);
    bool isGenerator(command& command);

    Server server;
    std::unordered_map<command, handler> handlers;
    std::unordered_set<command> generators;
};

#endif // EVENTHANDLER_H
