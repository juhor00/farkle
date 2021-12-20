#include "mainwindow.h"
#include "network.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    Network network("localhost");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
