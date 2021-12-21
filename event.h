#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "utilities.h"

class Event
{
public:
    Event(std::string& message);

    void print();
private:

    std::string command;
    std::vector<std::string> parameters;
};

#endif // EVENT_H
