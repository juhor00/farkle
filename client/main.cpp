#include "mainwindow.h"
#include "network.h"
#include "utilities.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    auto settings = utils::settingsParser("networkConfig.txt");
    string address = settings.at("ip-address");
    string port = settings.at("port");

    Network network(address, port);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
