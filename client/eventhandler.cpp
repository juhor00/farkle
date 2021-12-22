#include "eventhandler.h"


EventHandler::EventHandler(Network &s):
    server(s)
{
    handlers = {
        {"ROLL", &EventHandler::rollEvent},
        {"SHOW", &EventHandler::showEvent},
        {"BUST", &EventHandler::bustEvent},
               };

    generators = {
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

}

void EventHandler::showEvent(parameters &params)
{

}

void EventHandler::bustEvent(parameters &params)
{

}

void EventHandler::holdEvent(parameters &params)
{
    message msg = "HOLD ";
    msg += utils::join(params);
    server.sendToServer(msg);
}

void EventHandler::saveEvent(parameters &params)
{
    message msg = "SAVE ";
    msg += utils::join(params);
    server.sendToServer(msg);
}

bool EventHandler::isHandler(command &command)
{
    return handlers.find(command) != handlers.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators.find(command) != generators.end();
}
