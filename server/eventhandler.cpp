#include "eventhandler.h"
#include "server.h"

EventHandler::EventHandler(Server* s):
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

void EventHandler::createRollEvent(SOCKET client, dice dice)
{
    message msg = "ROLL ";
    msg += utils::join(dice);
    Event event(client, msg);
    sendEvent(event);
}

void EventHandler::createShowEvent(SOCKET client, diceValue diceValues)
{
    message msg = "SHOW ";

    dice dice(diceValues.size());
    for(auto& pair : diceValues){
        dice.insert(pair.first + ":" + pair.second);
    }
    Event event(client, msg);
    sendEvent(event);
}

void EventHandler::createBustEvent(SOCKET client)
{
    Event event(client, "BUST");
    sendEvent(event);
}

void EventHandler::holdEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [HOLD] Parameters: [" << utils::join(params) << "]" << std::endl;
}

void EventHandler::saveEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [SAVE] Parameters: [" << utils::join(params) << "]" << std::endl;
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
    server->sendToClient(client, msg);
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

