#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "eventhandler.h"

class EventHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onNoServerConnection();
    void onDisplayGame();


private slots:


private:

    void onRetryConnection();
    EventHandler* eventHandler;
};
#endif // MAINWINDOW_H
