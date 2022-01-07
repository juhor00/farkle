#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include "game/game.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

using message = std::string;

class Server;
class EventHandler;

typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler
{
public:

    EventHandler(Server* server);
    ~EventHandler();

    void removeClient(SOCKET client);

    bool handleEvent(Event& event);

    // Create events
    void createShowEvent(diceValues diceValues);
    void createBustEvent(player player);
    void createTurnEvent(player player);
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
    Game* game;
    SOCKET testClient;

    std::vector<SOCKET> clients;

    std::unordered_map<command, handler> handlers = {
        {"HOLD", &EventHandler::holdEvent},
        {"SAVE", &EventHandler::saveEvent},
        {"TEST", &EventHandler::testEvent},
    };
    std::unordered_set<command> generators = {
        "SHOW", "BUST", "TURN", "OVER", "ROUND", "TOTAL"
    };
};

#endif // EVENTHANDLER_H
