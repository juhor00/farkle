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
    std::string address = settings.at("ip-address");
    std::string port = settings.at("port");

    server = new Server(this, address, port);
    if(not server->isConnected()){
        mainWindow->onNoServerConnection();
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

bool EventHandler::retryConnection()
{
    return true;
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

}

void EventHandler::showEvent(parameters &params)
{

}

void EventHandler::bustEvent(parameters &params)
{

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
