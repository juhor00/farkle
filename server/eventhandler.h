#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include <map>

using parameters = std::vector<std::string>;

class EventHandler
{
public:
    EventHandler();
    void newEvent(Event& event);
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);

private:

    std::map<std::string, void(EventHandler::*)(parameters&)> handlers;
};

#endif // EVENTHANDLER_H
