#include "game.h"
#include "./eventhandler.h"


Game::Game(EventHandler *eventHandler):
    eventHandler(eventHandler),
    inTurn(0)
{

}

Game::~Game()
{

}

bool Game::hold(player player, dice dice)
{
    // Only the player in turn can hold dice
    if(not isInTurn(player)){
        return false;
    }

    // CODE HERE
    (void) dice;

    return true;
}

bool Game::save(player player, dice dice)
{
    // Only the player in turn can save dice
    if(not isInTurn(player)){
        return false;
    }

    // CODE HERE
    (void) dice;

    return true;
}

void Game::start()
{

}

void Game::changeTurn()
{
    inTurn = (inTurn + 1) % 2;
}

bool Game::isInTurn(player player)
{
    return player == inTurn;
}

void Game::showEvent(diceValues dice)
{
    eventHandler->createShowEvent(this, dice);
}

void Game::bustEvent(player player)
{
    eventHandler->createBustEvent(this, player);
}

void Game::turnEvent(player player)
{
    eventHandler->createTurnEvent(this, player);
}

void Game::overEvent()
{
    eventHandler->createOverEvent(this);
}
