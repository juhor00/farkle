#include "game.h"
#include "./eventhandler.h"


Game::Game(EventHandler *eventHandler):
    eventHandler(eventHandler), inTurn(0)
{

}

Game::~Game()
{

}

bool Game::hold(player player, dice /*dice*/)
{
    if(not isInTurn(player)){
        return false;
    }

    // CODE HERE

    return true;
}

bool Game::save(player player, dice /*dice*/)
{
    if(not isInTurn(player)){
        return false;
    }

    // CODE HERE

    return true;
}

void Game::changeTurn()
{
    inTurn = (inTurn + 1) % 2;
}

bool Game::isInTurn(player player)
{
    return player == inTurn;
}

void Game::showEvent(diceValues /*dice*/)
{

}

void Game::bustEvent(player /*player*/)
{

}

void Game::turnEvent(player /*player*/)
{

}

void Game::overEvent()
{

}
