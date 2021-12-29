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

    void rollDice(std::unordered_set<std::string>& dice);
    void rollDice(unordered_set<int>& dice);

    void showDice(std::unordered_map<std::string, std::string>& diceValues);
    void showDice(unordered_map<int, int>& diceValues);

    void bust(std::string& player);
    void bust(int& player);

    void onNoServerConnection();
    void onDisplayGame();

private slots:
    // Called if can't connect at all
    void onDisplayNoConnection();

    // Called if connection is lost during game
    void onInformNoConnection();


    void on_pushButton_clicked();

private:
    // Send event methods
    void holdDice(unordered_set<string>& dice);
    void saveDice(unordered_set<string>& dice);

    Ui::MainWindow* ui;
    EventHandler* eventHandler;
};
#endif // MAINWINDOW_H
