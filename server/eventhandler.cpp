#include "eventhandler.h"

EventHandler::EventHandler()
{
    handlers = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };
}

bool EventHandler::newEvent(Event &event)
{
    command command = event.getCommand();
    if(not isValidCommand(command)){
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

bool EventHandler::isValidCommand(command &command)
{
    return handlers.find(command) != handlers.end();
}


