#include "eventhandler.h"
#include "mainwindow.h"


EventHandler::EventHandler(MainWindow* m):
    mainWindow(m)
{

    handlers = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };

    generators = {"HOLD", "SAVE"};

    // Network settings
    std::string settingsFile = "networkConfig.txt";
    auto settings = utils::settingsParser(settingsFile);

    if(not utils::verifySettings(settings)){
        std::cerr << "File " << settingsFile << " is invalid" << std::endl;
        // INVALID NETWORK SETTINGS, DO SOMETHING
    }
    address_ = settings.at("ip-address");
    port_ = settings.at("port");

    server = new Server(this, address_, port_);
    if(not server->isConnected()){
        mainWindow->onNoServerConnection();
    } else {
        mainWindow->onDisplayGame();
    }
}

EventHandler::~EventHandler()
{
    delete server;
}

bool EventHandler::handleEvent(Event &event)
{
    command command = event.getCommand();
    if(not isHandler(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    handler handler = handlers.at(command);
    (this->*handler)(parameters);

    return true;
}

void EventHandler::retryConnection()
{
    if(not server->isConnected()){
        delete server;
        server = new Server(this, address_, port_);
    }
    if(server->isConnected()){
        mainWindow->onDisplayGame();
    } else {
        mainWindow->onNoServerConnection();
    }
}

void EventHandler::createSaveEvent(dice dice)
{
    message msg = "SAVE " + utils::join(dice);
    Event event(msg);
    sendEvent(event);
}

void EventHandler::createHoldEvent(dice dice)
{
    message msg = "HOLD " + utils::join(dice);
    Event event(msg);
    sendEvent(event);
}

void EventHandler::rollEvent(parameters &params)
{
    dice dice = paramsToDice(params);
    mainWindow->rollDice(dice);
}

void EventHandler::showEvent(parameters &params)
{
    diceValues dice = paramsToDiceValues(params);
    mainWindow->showDice(dice);
}

void EventHandler::bustEvent(parameters &params)
{
    player player = params.front();
    mainWindow->bust(player);
}

void EventHandler::noConnectionEvent()
{
    mainWindow->onNoServerConnection();
}

bool EventHandler::sendEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    message msg = command + " " + utils::join(parameters);
    server->sendToServer(msg);
    return true;
}

bool EventHandler::isHandler(command &command)
{
    return handlers.find(command) != handlers.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators.find(command) != generators.end();
}

dice EventHandler::paramsToDice(parameters &params)
{
    dice dice(params.begin(), params.end());
    return dice;
}

diceValues EventHandler::paramsToDiceValues(parameters &params)
{
    diceValues dice(params.size());
    for(auto& pair : params){
        auto diceValue = utils::split(pair);
        dice.insert({diceValue.at(0), diceValue.at(1)});
    }
    return dice;
}
