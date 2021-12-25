#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), eventHandler(new EventHandler(this))
{
}

MainWindow::~MainWindow()
{
    delete eventHandler;
}

void MainWindow::onNoServerConnection()
{
    qDebug() << "Display: No connection";
}

void MainWindow::onDisplayGame()
{
    qDebug() << "Display: Game window";
}

void MainWindow::onRetryConnection()
{
    qDebug() << "Retry connection";
    eventHandler->retryConnection();
}

