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

bool EventHandler::handleEvent(Event &event)
{
    command command = event.getCommand();
    if(not isHandler(command)){
        return false;
    }
    parameters parameters = event.getParameters();
    handler handler = handlers.at(command);
    SOCKET client = event.getClient();
    (this->*handler)(client, parameters);

    return true;
}

void EventHandler::createRollEvent(SOCKET client, diceStr dice)
{
    message msg = "ROLL ";
    msg += utils::join(dice);
    Event event(client, msg);
    sendEvent(event);
}

void EventHandler::createRollEvent(SOCKET client, diceInt dice)
{
    createRollEvent(client, toStr(dice));

}

void EventHandler::holdEvent(SOCKET client, parameters &params)
{

}

void EventHandler::saveEvent(SOCKET client, parameters &params)
{

}

bool EventHandler::sendEvent(Event &event)
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

bool EventHandler::isHandler(command &command)
{
    return handlers.find(command) != handlers.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators.find(command) != generators.end();
}

diceStr EventHandler::toStr(diceInt dice)
{
    diceStr result(dice.size());
    for(int d : dice){
        result.insert(std::to_string(d));
    }
    return result;
}



