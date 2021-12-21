#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include "server.h"
#include <unordered_map>

using message = std::string;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);
    typedef void (EventHandler::*generator)(parameters&);

    EventHandler(Server& server);

    bool generateEvent(Event& event);
    bool handleEvent(Event& event);

    // Generators
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);

    // Handlers
    void holdEvent(parameters& params);
    void saveEvent(parameters& params);


private:

    bool isHandler(command& command);
    bool isGenerator(command& command);

    Server server;

    std::unordered_map<command, generator> generators;
    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
