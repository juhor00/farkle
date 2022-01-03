#include "eventhandler.h"
#include "server.h"

EventHandler::EventHandler(Server* s):
    server(s), testClient(INVALID_SOCKET)
{

    handlers = {
        {"HOLD", &EventHandler::holdEvent},
        {"SAVE", &EventHandler::saveEvent},
        {"TEST", &EventHandler::testEvent},
    };
    generators = {"ROLL", "SHOW", "BUST", "TURN", "OVER"};

}

void EventHandler::removeClient(SOCKET client)
{
    clients.erase(client);
}

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    SOCKET client = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();
    std::cout << "Client: " << client << " Test client: " << testClient << std::endl;
    if(client == testClient){
        // Pass command to others
        testBroadcast(event);
        return true;
    }
    else if(not isHandler(command)){
        return false;
    }

    // Handle normally
    clients.insert(client);
    handler handler = handlers.at(command);
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

void EventHandler::createBustEvent(SOCKET client, SOCKET player)
{

}

void EventHandler::createTurnEvent(SOCKET client, SOCKET player)
{

}

void EventHandler::createOverEvent(SOCKET client)
{

}


void EventHandler::holdEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [HOLD] Parameters: [" << utils::join(params) << "]" << std::endl;
}

void EventHandler::saveEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [SAVE] Parameters: [" << utils::join(params) << "]" << std::endl;
}

void EventHandler::testEvent(SOCKET client, parameters&)
{
    testClient = client;
    std::cout << "Client: [" << client << "] Event: [TEST]" << std::endl;
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

void EventHandler::testBroadcast(Event &event)
{
    SOCKET sender = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();

    std::unordered_set<std::string> broadcastTo(clients.size());
    for(auto c : clients){
        if(c != sender){
            broadcastTo.insert(std::to_string(c));
        }
    }
    std::cout << "Broadcasting to: " << utils::join(broadcastTo) << std::endl;

    for(SOCKET sendTo : clients){
        if(sendTo != sender){
            Event eventToSend(sendTo, command, parameters);
            sendEvent(eventToSend);
        }
    }
}

