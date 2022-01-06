#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventhandler.h"
#include "dicegui.h"
#include <QMainWindow>
#include <QDebug>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>


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
    void showDice(unordered_map<int, int>& diceValues);
    void bust(int player);
    void setTurn(int player);
    void gameover(int player);
    void setRoundPoints(int player, int points);
    void setTotalPoints(int player, int points);

    // General events
    void onNoServerConnection();
    void onDisplayGame();

private slots:

    // ONLY FOR TESTING RETRY CONNECTION
    // Can be removed
    void on_pushButton_clicked();

    void onDiceClicked(int row, int nmbr);

private:

    const vector<string> DICE_IMAGES = {"1.png", "2.png", "3.png",
                                                  "4.png", "5.png", "6.png"};

    const int WINDOW_W = 1000;
    const int WINDOW_H = 700;

    const int DICE_SIZE = 80;

    void initImages();
    void initGUI();

    // Send event methods
    void holdDice(unordered_set<int>& dice);
    void saveDice(unordered_set<int>& dice);



    Ui::MainWindow* ui;
    EventHandler* eventHandler;

    vector<QPixmap> diceImages;
    vector<vector<DiceGUI*>> dices;
};
#endif // MAINWINDOW_H
