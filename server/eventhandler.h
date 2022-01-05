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

    void removeClient(SOCKET client);

    bool handleEvent(Event& event);

    // Create events
    void createRollEvent(dice dice);
    void createShowEvent(diceValue diceValues);
    void createBustEvent(SOCKET player);
    void createTurnEvent(SOCKET player);
    void createOverEvent();


private:

    // Handlers
    void holdEvent(SOCKET client, parameters& params);
    void saveEvent(SOCKET client, parameters& params);
    void testEvent(SOCKET client, parameters&);

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);

    void testBroadcast(Event& event);
    void broadcast(Event& event);

    Server* server;
    SOCKET testClient;

    std::unordered_set<SOCKET> clients;

    std::unordered_map<command, handler> handlers;
    std::unordered_set<command> generators;
};

#endif // EVENTHANDLER_H
