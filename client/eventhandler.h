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
using playerScore = std::pair<int,int>;

class EventHandler;
typedef void (EventHandler::*handler)(parameters&);
typedef void (EventHandler::*generator)(parameters&);

class MainWindow;

class EventHandler
{
public:

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




private:

    // Game event handlers
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);
    void turnEvent(parameters& params);
    void overEvent(parameters&);
    void roundEvent(parameters& params);
    void totalEvent(parameters& params);

    bool sendEvent(Event& event);
    bool isHandler(command& command);
    bool isGenerator(command& command);

    Server* server;
    std::string address_;
    std::string port_;
    MainWindow* mainWindow;

    std::unordered_set<command> generators;
    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
