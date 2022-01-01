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
    auto params = utils::toString(dice);
    message msg = "SAVE " + utils::join(params);
    Event event(msg);
    sendEvent(event);
}

void EventHandler::createHoldEvent(dice dice)
{
    auto params = utils::toString(dice);
    message msg = "HOLD " + utils::join(params);
    Event event(msg);
    sendEvent(event);
}

void EventHandler::noConnectionEvent()
{
    mainWindow->onNoServerConnection();
}

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    command command = event.getCommand();
    if(not isHandler(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    handler handler = handlers.at(command);
    (this->*handler)(parameters);

    return true;
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
    player player = utils::toInt(params.front());
    mainWindow->bust(player);
}

void EventHandler::turnEvent(parameters &params)
{
    player player = utils::toInt(params.front());
    mainWindow->setTurn(player);
}

void EventHandler::overEvent(parameters &)
{
    mainWindow->gameover();
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
    std::unordered_set<std::string> p(params.begin(), params.end());
    dice dice = utils::toInt(p);
    return dice;
}

diceValues EventHandler::paramsToDiceValues(parameters &params)
{
    diceValues dice(params.size());
    for(auto& pair : params){
        auto diceValue = utils::split(pair);
        dice.insert({utils::toInt(diceValue.at(0)), utils::toInt(diceValue.at(1))});
    }
    return dice;
}
