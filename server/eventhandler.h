#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../event.h"
#include <map>

class EventHandler
{
public:
    typedef void (EventHandler::*handler)(parameters&);

    EventHandler();
    void newEvent(Event& event);
    void rollEvent(parameters& params);
    void showEvent(parameters& params);
    void bustEvent(parameters& params);

private:

    std::map<command, handler> handlers;
};

#endif // EVENTHANDLER_H
