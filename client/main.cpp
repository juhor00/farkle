#include "mainwindow.h"
#include "network.h"
#include "../utilities.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    string settingsFile = "networkConfig.txt";
    auto settings = utils::settingsParser(settingsFile);

    if(not utils::verifySettings(settings)){
        cerr << "File " << settingsFile << " is invalid" << endl;
        return EXIT_FAILURE;
    }
    string address = settings.at("ip-address");
    string port = settings.at("port");

    Network network(address, port);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
