#ifndef GAME_H
#define GAME_H

#include <unordered_set>
#include <unordered_map>

using dice = std::unordered_set<int>;
using diceValues = std::unordered_map<int, int>;
using player = int;

class EventHandler;

class Game
{
public:
    Game(EventHandler* eventHandler);
    ~Game();

    // Events
    bool hold(player player, dice dice);
    bool save(player player, dice dice);

    // Start the game
    // Called by event handler
    void start();

private:

    void changeTurn();
    bool isInTurn(player player);

    // Events
    void showEvent(diceValues dice);
    void bustEvent(player player);
    void turnEvent(player player);
    void overEvent();


    EventHandler* eventHandler;
    player inTurn;
};

#endif // GAME_H
