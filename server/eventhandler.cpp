#include "eventhandler.h"

EventHandler::EventHandler(Server& s):
    server(s)
{
    generators = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };

    handlers = {
        {"HOLD", &EventHandler::holdEvent},
        {"SAVE", &EventHandler::saveEvent},
    };

}

bool EventHandler::generateEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    generator generator = generators.at(command);
    (this->*generator)(parameters);
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
    message msg = "ROLL ";
    msg += utils::join(params);
    //server.sendToClient()
}

void EventHandler::showEvent(parameters &params)
{
    message msg = "SHOW ";
    msg += utils::join(params);
    //server.sendToClient()
}

void EventHandler::bustEvent(parameters &params)
{
    message msg = "BUST ";
    msg += utils::join(params);
    //server.sendToClient()
}

void EventHandler::holdEvent(parameters &params)
{

}

void EventHandler::saveEvent(parameters &params)
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


