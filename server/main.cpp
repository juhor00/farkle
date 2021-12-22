#include <iostream>
#include "server.h"
#include "eventhandler.h"

using namespace std;



int main()
{

    Server server;
    EventHandler eventHandler(&server);
    server.linkEventHandler(&eventHandler);


    return EXIT_SUCCESS;
}
