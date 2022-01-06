#ifndef GAME_H
#define GAME_H

class EventHandler;

class Game
{
public:
    Game(EventHandler* eventHandler);

private:

    EventHandler* eventHandler;
};

#endif // GAME_H
