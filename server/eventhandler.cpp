#include "eventhandler.h"

EventHandler::EventHandler(Server& s):
    server(s)
{

    handlers = {
        {"HOLD", &EventHandler::holdEvent},
        {"SAVE", &EventHandler::saveEvent},
    };
    generators = {"ROLL", "SHOW", "BUST"};

}

bool EventHandler::generateEvent(Event &event)
{
    command command = event.getCommand();
    if(not isGenerator(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    SOCKET client = event.getClient();
    message msg = command + " " + utils::join(parameters);
    server.sendToClient(client, msg);
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
    SOCKET client = event.getClient();
    (this->*handler)(parameters, client);

    return true;
}

void EventHandler::holdEvent(parameters &params, SOCKET client)
{

}

void EventHandler::saveEvent(parameters &params, SOCKET client)
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



