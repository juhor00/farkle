#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include <unordered_map>

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);

    EventHandler();
    bool newEvent(Event& event);
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);

private:

    bool isValidCommand(command& command);

    std::unordered_map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
