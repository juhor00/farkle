#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "utilities.h"

using parameters = std::vector<std::string>;

class Event
{
public:
    Event(std::string& message);
    std::string getCommand();
    parameters getParameters();
    void print();

private:

    std::string command;
    parameters parameters;
};

#endif // EVENT_H
