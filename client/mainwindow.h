#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventhandler.h"

class EventHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void onRetryConnection();

public slots:
    void onNoServerConnection();


private slots:


private:
    EventHandler* eventHandler;
};
#endif // MAINWINDOW_H
