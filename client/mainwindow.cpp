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

void MainWindow::rollDice(unordered_set<int> &dice)
{

}

void MainWindow::showDice(unordered_map<int, int> &diceValues)
{

}

void MainWindow::bust(int player)
{

}
void MainWindow::setTurn(int player)
{

}

void MainWindow::gameover()
{

}

void MainWindow::setRoundPoints(int player, int points)
{

}

void MainWindow::setTotalPoints(int player, int points)
{

}

void MainWindow::onNoServerConnection()
{
    qDebug() << "No server connection";
    cerr << "GUI: No server connection" << endl;
}

void MainWindow::onDisplayGame()
{
    qDebug() << "Display: Game";
}

void MainWindow::onDisplayNoConnection()
{

}

// Don't change this
void MainWindow::holdDice(unordered_set<int> &dice)
{
    eventHandler->createHoldEvent(dice);
}

// Don't change this
void MainWindow::saveDice(unordered_set<int> &dice)
{
    eventHandler->createSaveEvent(dice);
}

void MainWindow::on_pushButton_clicked()
{
    eventHandler->retryConnection();
}

