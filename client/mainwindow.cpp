#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), eventHandler(new EventHandler(this))
{
}

MainWindow::~MainWindow()
{
    delete eventHandler;
}

