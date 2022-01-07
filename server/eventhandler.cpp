#include "eventhandler.h"
#include "server.h"

EventHandler::EventHandler(Server* s):
    server(s), game(new Game(this)), testClient(INVALID_SOCKET)
{
}

EventHandler::~EventHandler()
{

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

void EventHandler::createShowEvent(std::unordered_map<std::string, std::string> diceValues)
{
    message msg = "SHOW ";

    std::unordered_set<std::string> dice(diceValues.size());
    for(auto& pair : diceValues){
        dice.insert(pair.first + ":" + pair.second);
    }
    Event event(msg);
    broadcast(event);
}

void EventHandler::createBustEvent(SOCKET player)
{
    message bust = "BUST ";
    for(auto client : clients){
        message msg = bust + (char) (client != player);
        Event event(client, msg);
        sendEvent(event);
    }
}

void EventHandler::createTurnEvent(SOCKET player)
{
    message turn = "TURN ";
    for(auto client : clients){
        message msg = turn + (char) (client != player);
        Event event(client, msg);
        sendEvent(event);
    }
}

void EventHandler::createOverEvent()
{
    Event event("OVER");
    broadcast(event);
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

void EventHandler::broadcast(Event &event)
{
    std::cout << "Broadcasting" << std::endl;
    for(auto client : clients){
        event.setClient(client);
        sendEvent(event);
    }
}

