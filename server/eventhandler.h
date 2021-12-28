#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using message = std::string;
using dice = std::unordered_set<std::string>;
using diceValue = std::unordered_map<std::string, std::string>;

class Server;
class EventHandler;

typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler
{
public:

    EventHandler(Server* server);

    bool handleEvent(Event& event);

    // Create events
    void createRollEvent(SOCKET client, dice dice);
    void createShowEvent(SOCKET client, diceValue diceValues);
    void createBustEvent(SOCKET client);

    // Handlers
    void holdEvent(SOCKET client, parameters& params);
    void saveEvent(SOCKET client, parameters& params);


private:

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);

    Server* server;
    std::unordered_map<command, handler> handlers;
    std::unordered_set<command> generators;
};

#endif // EVENTHANDLER_H
