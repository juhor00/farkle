#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include "server.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using message = std::string;

using diceStr = std::unordered_set<std::string>;
using diceInt = std::unordered_set<int>;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(SOCKET, parameters&);
    typedef void (EventHandler::*generator)(SOCKET, parameters&);

    EventHandler(Server& server);

    bool handleEvent(Event& event);

    // Create events
    void createRollEvent(SOCKET client, diceStr dice);
    void createRollEvent(SOCKET client, diceInt dice);

    // Handlers
    void holdEvent(SOCKET client, parameters& params);
    void saveEvent(SOCKET client, parameters& params);


private:

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);
    diceStr toStr(diceInt dice);

    Server server;
    std::unordered_map<command, handler> handlers;
    std::unordered_set<command> generators;
};

#endif // EVENTHANDLER_H
