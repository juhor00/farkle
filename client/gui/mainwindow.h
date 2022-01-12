#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventhandler.h"
#include "dice.h"
#include <QMainWindow>
#include <QDebug>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <QPushButton>
#include <algorithm>


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

protected:
    void resizeEvent(QResizeEvent* event) override;

private:

    const vector<string> DICE_IMAGES = {"1.png", "2.png", "3.png",
                                        "4.png", "5.png", "6.png",
                                        "1d.png", "2d.png", "3d.png",
                                        "4d.png", "5d.png", "6d.png"};

    const int WIN_MIN_W = 400;
    const int WIN_MIN_H = 225;


    const int WIN_NORMAL_W = 1600;
    const int WIN_NORMAL_H = 900;

    const int DICE_SIZE = 80;

    const int DICE_ROW_X = 60;
    const vector<int> DICE_ROW_Y = {600, 60, 360};
    const int DICE_GAP = 90;


    void scaleW(int& variable, int basevalue);
    void scaleH(int& variable, int basevalue);

    void resizeGUI();
    void drawGUI();

    void initImages();
    void initGUI();

    // Send event methods
    void holdDice(unordered_set<int>& dice);
    void saveDice(unordered_set<int>& dice);


    Ui::MainWindow* ui;
    // EventHandler* eventHandler;

    int winW = WIN_NORMAL_W;
    int winH = WIN_NORMAL_H;

    int diceSize = DICE_SIZE;
    int diceRowX = DICE_ROW_X;
    vector<int> diceRowY = DICE_ROW_Y;
    int diceGap = DICE_GAP;

    vector<QPixmap> diceImages;
    vector<vector<DiceGUI*>> dices;

    QPushButton* rollDice;
    QPushButton* bankScore;

    int player = 0;
};
#endif // MAINWINDOW_H
