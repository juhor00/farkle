#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "utilities.h"

using command = std::string;
using parameters = std::vector<std::string>;

class Event
{
public:
    Event(std::string& message);
    command getCommand();
    parameters getParameters();
    void print();

private:

    command command;
    parameters parameters;
};

#endif // EVENT_H
