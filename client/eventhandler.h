#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "../event.h"
#include "server.h"
#include <unordered_map>
#include <unordered_set>

using message = std::string;
using dice = std::unordered_set<int>;
using diceValues = std::unordered_map<int, int>;
using player = int;

class MainWindow;

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);
    typedef void (EventHandler::*generator)(parameters&);

    EventHandler(MainWindow* m);
    ~EventHandler();

    // Create general events
    void retryConnection();

    // Create game events
    void createSaveEvent(dice dice);
    void createHoldEvent(dice dice);

    // General event handlers
    void noConnectionEvent();
    bool handleEvent(Event& event);

    // Game event handlers
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);
    void turnEvent(parameters& params);
    void overEvent(parameters&);




private:

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);
    dice paramsToDice(parameters& params);
    diceValues paramsToDiceValues(parameters& params);

    Server* server;
    std::string address_;
    std::string port_;
    MainWindow* mainWindow;

    std::unordered_set<command> generators;
    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
