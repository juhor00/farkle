#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "../event.h"
#include "network.h"
#include <unordered_map>

using message = std::string;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);
    typedef void (EventHandler::*generator)(parameters&);

    EventHandler(Network& server);

    bool generateEvent(Event& event);
    bool handleEvent(Event& event);

    // Handlers
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);

    // Generators
    void holdEvent(parameters& params);
    void saveEvent(parameters& params);


private:

    bool isHandler(command& command);
    bool isGenerator(command& command);

    Network server;

    std::unordered_map<command, generator> generators;
    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
