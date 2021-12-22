#include "eventhandler.h"


EventHandler::EventHandler(Network &s):
    server(s)
{
    handlers = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };

    generators = {"HOLD", "SAVE"};
}

bool EventHandler::generateEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    message msg = command + " " + utils::join(parameters);
    server.sendToServer(msg);
    return true;
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

void EventHandler::rollEvent(parameters &params)
{

}

void EventHandler::showEvent(parameters &params)
{

}

void EventHandler::bustEvent(parameters &params)
{

}

bool EventHandler::isHandler(command &command)
{
    return handlers.find(command) != handlers.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators.find(command) != generators.end();
}
