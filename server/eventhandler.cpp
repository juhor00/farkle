#include "eventhandler.h"

// PUBLIC

EventHandler::EventHandler():
    latestGame_(new Game(this)),
    clientsByGame_({}),
    testClient_(INVALID_SOCKET)
{
    clientsByGame_.insert({latestGame_, {}});
    acceptClients();
}

EventHandler::~EventHandler()
{
    for(auto& [game, clients] : clientsByGame_){
        delete game;
    }
    if(latestGame_ != nullptr){
        delete latestGame_;
    }
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



// PROTECTED

bool EventHandler::handleEvent(Event &event)
{
    event.print();
    SOCKET client = event.getClient();
    command command = event.getCommand();
    parameters parameters = event.getParameters();

    //
    // TESTING BEGIN
    //

    // Receive from test client
    if(client == testClient_){
        // Pass command to others
        testBroadcast(event);
        return true;
    }

    // Send to test client
    if(testClient_ != INVALID_SOCKET){
        std::cout << "sending to test client" << std::endl;
        event.setClient(testClient_);
        sendEvent(event);
    }

    //
    // TESTING END
    //

    if(not isHandler(command)){
        return false;
    }

    // Handle normally
    handler handler = handlers_.at(command);
    (this->*handler)(client, parameters);
    return true;
}

bool EventHandler::addClient(SOCKET client)
{
    if(!Server::addClient(client)){
        return false;
    }
    //
    // ONLY FOR TESTING
    if(client == testClient_){
        return true;
    }
    // ONLY FOR TESTING
    //

    if(hasClient(client)){
        return true;
    }
    clients_.insert(client);

    // Add to latest game's client list
    auto clients = getClientsByGame(latestGame_);
    clients.push_back(client);
    clientsByGame_.at(latestGame_) = clients;

    // Start game and create new
    if(clients.size() == 2){
        latestGame_->start();
        createNewGame();
    }
    return true;
}

bool EventHandler::removeClient(SOCKET client)
{
    if(not Server::removeClient(client)){
        return false;
    }
    if(not hasClient(client)){
        return false;
    }
    // Find list of clients of the game where client is
    Game* game = getGameByClient(client);
    std::vector<SOCKET> clients = getClientsByGame(game);
    clients.erase(std::find(clients.begin(), clients.end(), client));
    clientsByGame_.at(game) = clients;
    clients_.erase(client);

    if(clients.empty() and clientsByGame_.size() > 1){
        clientsByGame_.erase(game);
        delete game;
    }
    return true;

}



// PRIVATE

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

void EventHandler::clickEvent(SOCKET client, parameters &params)
{
    std::cout << "Client: [" << client << "] Event: [CLICK] Parameters: [" << utils::join(params) << "]" << std::endl;
    Game* game = getGameByClient(client);
    auto clients = getClientsByGame(game);
    for(auto sendTo : clients){
        if(client != sendTo){
            Event event(sendTo, "CLICK", params);
            sendEvent(event);
            return;
        }
    }
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
    sendToClient(client, msg);
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

void EventHandler::createNewGame()
{
    latestGame_ = new Game(this);
    clientsByGame_.insert({latestGame_, {}});
}

bool EventHandler::hasClient(SOCKET client)
{
    return std::find(clients_.begin(), clients_.end(), client) != clients_.end();
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


