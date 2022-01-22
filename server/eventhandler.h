#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include "game/game.h"
#include "server.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

using message = std::string;
class EventHandler;

typedef void (EventHandler::*handler)(SOCKET, parameters&);

class EventHandler : protected Server
{
public:

    EventHandler();
    ~EventHandler();

    // Create events
    void createShowEvent(Game* game, diceValues diceValues);
    void createBustEvent(Game* game, player player);
    void createTurnEvent(Game* game, player player);
    void createOverEvent(Game* game);

protected:

    bool handleEvent(Event& event) override;
    bool addClient(SOCKET client) override;
    bool removeClient(SOCKET client) override;


private:

    // Handlers
    void holdEvent(SOCKET client, parameters& params);
    void saveEvent(SOCKET client, parameters& params);
    void clickEvent(SOCKET client, parameters& params);
    void testEvent(SOCKET client, parameters&);

    // Event sending
    bool sendEvent(Event& event);
    void testBroadcast(Event& event);
    void broadcast(Event& event);
    void broadcast(std::vector<SOCKET> clients, Event& event);

    // Other event methods
    bool isHandler(command& command);
    bool isGenerator(command& command);

    // Game methods
    void createNewGame();
    bool hasClient(SOCKET client);
    int getIndex(std::vector<SOCKET> clients, SOCKET client);
    Game *getGameByClient(SOCKET client);
    std::vector<SOCKET> getClientsByGame(Game* game);

    // Attributes
    Game* latestGame_;
    std::unordered_map<Game*, std::vector<SOCKET>> clientsByGame_;
    SOCKET testClient_;
    std::unordered_set<SOCKET> clients_;

    // Event attributes
    std::unordered_map<command, handler> handlers_ = {
        {"HOLD", &EventHandler::holdEvent},
        {"SAVE", &EventHandler::saveEvent},
        {"CLICK", &EventHandler::clickEvent},
        {"TEST", &EventHandler::testEvent},
    };
    std::unordered_set<command> generators_ = {
        "CLICK", "SHOW", "BUST", "TURN", "OVER", "ROUND", "TOTAL"
    };
};

#endif // EVENTHANDLER_H
