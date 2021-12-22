#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "../event.h"
#include "network.h"
#include <unordered_map>
#include <unordered_set>

using message = std::string;
using dice = std::unordered_set<std::string>;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);
    typedef void (EventHandler::*generator)(parameters&);

    EventHandler(Network& server);

    bool handleEvent(Event& event);

    // Create events
    void createSaveEvent(dice dice);
    void createHoldEvent(dice dice);

    // Handlers
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);


private:

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);

    Network server;

    std::unordered_set<command> generators;
    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
