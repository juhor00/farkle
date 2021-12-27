#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void holdDice(unordered_set<string>& dice);
    void saveDice(unordered_set<string>& dice);

public slots:
    void rollDice(std::unordered_set<std::string>& dice);
    void showDice(std::unordered_map<std::string, std::string>& diceValues);
    void bust();

private slots:
    // Delete this if you prefer to use string instead of int
    void rollDice(unordered_set<int>& dice);
    void showDice(unordered_map<int, int>& diceValues);


private:
    Ui::MainWindow* ui;
    EventHandler* eventHandler;
};
#endif // MAINWINDOW_H
