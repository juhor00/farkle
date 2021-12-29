#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "eventhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class EventHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    // Game events
    void rollDice(unordered_set<int>& dice);
    void showDice(unordered_map<int, int>& diceValues);
    void bust(int& player);
    void setTurn(int& player);
    void gameover();

    // General events
    void onNoServerConnection();
    void onDisplayGame();

private slots:
    // idk if needed
    void onDisplayNoConnection();

    // ONLY FOR TESTING RETRY CONNECTION
    // Can be removed
    void on_pushButton_clicked();

private:
    // Send event methods
    void holdDice(unordered_set<int>& dice);
    void saveDice(unordered_set<int>& dice);

    Ui::MainWindow* ui;
    EventHandler* eventHandler;
};
#endif // MAINWINDOW_H
