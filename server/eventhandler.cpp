#include "eventhandler.h"

EventHandler::EventHandler()
{
    handlers = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };
}

void EventHandler::newEvent(Event &event)
{
    command command = event.getCommand();
    parameters parameters = event.getParameters();
    handler handler = handlers.at(command);
    (this->*handler)(parameters);
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


