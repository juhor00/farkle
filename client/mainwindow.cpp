#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    eventHandler(new EventHandler(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete eventHandler;
}

// Don't change this
void MainWindow::rollDice(std::unordered_set<string> &dice)
{
    unordered_set<int> diceInt(dice.size());
    for(auto& die : dice){
        diceInt.insert(stoi(die));
    }
    rollDice(diceInt);
}

void MainWindow::rollDice(unordered_set<int> &dice)
{

}

// Don't change this
void MainWindow::showDice(std::unordered_map<string, string> &diceValues)
{
    unordered_map<int, int> diceValuesInt(diceValues.size());
    for(auto& pair : diceValues){
        diceValuesInt.insert({stoi(pair.first), stoi(pair.second)});
    }
    showDice(diceValuesInt);
}

void MainWindow::showDice(unordered_map<int, int> &diceValues)
{

}

// Don't change this
void MainWindow::bust(std::string& player)
{
    int playerInt = stoi(player);
    bust(playerInt);
}

void MainWindow::bust(int &player)
{

}

void MainWindow::onNoServerConnection()
{
    qDebug() << "No server connection";
}

void MainWindow::onDisplayGame()
{
    qDebug() << "Display: Game";
}

void MainWindow::onDisplayNoConnection()
{

}

void MainWindow::onInformNoConnection()
{

}

// Don't change this
void MainWindow::holdDice(unordered_set<string> &dice)
{
    eventHandler->createHoldEvent(dice);
}

// Don't change this
void MainWindow::saveDice(unordered_set<string> &dice)
{
    eventHandler->createSaveEvent(dice);
}
