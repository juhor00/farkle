#include "mainwindow.h"
#include "network.h"
#include "../utilities.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::string settingsFile = "networkConfig.txt";
    auto settings = utils::settingsParser(settingsFile);

    if(not utils::verifySettings(settings)){
        std::cerr << "File " << settingsFile << " is invalid" << std::endl;
        return EXIT_FAILURE;
    }
    std::string address = settings.at("ip-address");
    std::string port = settings.at("port");

    Network network(address, port);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
