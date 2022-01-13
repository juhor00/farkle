#include "eventhandler.h"
#include "server.h"

EventHandler::EventHandler(Server* s):
    server_(s),
    latestGame_(new Game(this)),
    clientsByGame_({}),
    testClient_(INVALID_SOCKET)
{
    clientsByGame_.insert({latestGame_, {}});
}

EventHandler::~EventHandler()
{
    for(auto& [game, clients] : clientsByGame_){
        delete game;
    }
    delete server_;
}

void EventHandler::removeClient(SOCKET client)
{
    clients_.erase(client);
}

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    SOCKET client = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();

    //
    // TESTING ONLY
    //
    if(client == testClient_){
        // Pass command to others
        testBroadcast(event);
        return true;
    }

    if(not isHandler(command)){
        return false;
    }

    if(not hasClient(client)){
        addClient(client);
    }

    // Handle normally
    handler handler = handlers_.at(command);
    (this->*handler)(client, parameters);
    return true;
}

void EventHandler::createShowEvent(Game* game, diceValues diceValues)
{
    auto clients = getClientsByGame(game);

    message msg = "SHOW ";
    std::unordered_set<std::string> dice(diceValues.size());
    for(auto& pair : diceValues){
        std::string dieValue = utils::toString(pair.first) + ":" + utils::toString(pair.second);
        dice.insert(dieValue);
    }
    Event event(msg);
    broadcast(clients, event);
}

void EventHandler::createBustEvent(Game* game, player player)
{
    auto clients = getClientsByGame(game);

    message bust = "BUST ";
    for(auto client : clients){
        message msg = bust + (char) (client != clients.at(player));
        Event event(client, msg);
        sendEvent(event);
    }
}

void EventHandler::createTurnEvent(Game* game, player player)
{
    auto clients = getClientsByGame(game);

    message turn = "TURN ";
    for(auto client : clients){
        message msg = turn + (char) (client != clients.at(player));
        Event event(client, msg);
        sendEvent(event);
    }
}

void EventHandler::createOverEvent(Game* game)
{
    auto clients = getClientsByGame(game);
    Event event("OVER");
    broadcast(clients, event);
}


void EventHandler::holdEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [HOLD] Parameters: [" << utils::join(params) << "]" << std::endl;
    std::unordered_set<std::string> paramsSet(params.begin(), params.end());
    dice dice = utils::toInt(paramsSet);
    Game* game = getGameByClient(client);
    auto clients = getClientsByGame(game);
    game->hold(getIndex(clients, client), dice);
}

void EventHandler::saveEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [SAVE] Parameters: [" << utils::join(params) << "]" << std::endl;
    std::unordered_set<std::string> paramsSet(params.begin(), params.end());
    dice dice = utils::toInt(paramsSet);
    Game* game = getGameByClient(client);
    auto clients = getClientsByGame(game);
    game->save(getIndex(clients, client), dice);
}

void EventHandler::testEvent(SOCKET client, parameters&)
{
    testClient_ = client;
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
    server_->sendToClient(client, msg);
    return true;
}

void EventHandler::testBroadcast(Event &event)
{
    SOCKET sender = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();

    std::unordered_set<std::string> broadcastTo(clients_.size());
    for(auto c : clients_){
        if(c != sender){
            broadcastTo.insert(std::to_string(c));
        }
    }
    std::cout << "Broadcasting to: " << utils::join(broadcastTo) << std::endl;

    for(SOCKET sendTo : clients_){
        if(sendTo != sender){
            Event eventToSend(sendTo, command, parameters);
            sendEvent(eventToSend);
        }
    }
}

void EventHandler::broadcast(Event &event)
{
    std::cout << "Broadcasting" << std::endl;
    for(auto client : clients_){
        event.setClient(client);
        sendEvent(event);
    }
}

void EventHandler::broadcast(std::vector<SOCKET> clients, Event &event)
{
    for(auto client : clients){
        event.setClient(client);
        sendEvent(event);
    }
}

bool EventHandler::isHandler(command &command)
{
    return handlers_.find(command) != handlers_.end();
}

bool EventHandler::isGenerator(command &command)
{
    return generators_.find(command) != generators_.end();
}

bool EventHandler::hasClient(SOCKET client)
{
    return std::find(clients_.begin(), clients_.end(), client) != clients_.end();
}

void EventHandler::addClient(SOCKET client)
{
    clients_.insert(client);
    auto clients = getClientsByGame(latestGame_);
    if(clients.size() >= 2){
        latestGame_ = new Game(this);
        clients = {};
    }
    clients.push_back(client);
    clientsByGame_.at(latestGame_) = clients;
}

int EventHandler::getIndex(std::vector<SOCKET> clients, SOCKET client)
{
    return std::find(clients.begin(), clients.end(), client) - clients.begin();
}

Game *EventHandler::getGameByClient(SOCKET client)
{
    for(auto& [game, clients] : clientsByGame_){
        // Game has client
        if(std::find(clients.begin(), clients.end(), client) != clients.end()){
            return game;
        }
    }
    return nullptr;
}

std::vector<SOCKET> EventHandler::getClientsByGame(Game *game)
{
    return clientsByGame_.at(game);
}
