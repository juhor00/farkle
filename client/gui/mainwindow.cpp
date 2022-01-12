#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    // eventHandler(new EventHandler(this))
{
    ui->setupUi(this);

    this->setFixedSize(WINDOW_W, WINDOW_H);

    initImages();

    initGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    // delete eventHandler;
}

void MainWindow::showDice(unordered_map<int, int> &diceValues)
{
    //  VOID ONLY FOR REMOVING WARNINGS
    //  REMOVE WHEN ACTUALLY IMPLEMENTING
    (void)diceValues;
}

void MainWindow::bust(int player)
{
    (void)player;
}
void MainWindow::setTurn(int player)
{
    (void)player;
}

void MainWindow::gameover(int player)
{
    (void)player;
}

void MainWindow::setRoundPoints(int player, int points)
{
    (void)player;
    (void)points;
}

void MainWindow::setTotalPoints(int player, int points)
{
    (void)player;
    (void)points;
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

void MainWindow::onDiceClicked(int row, int nmbr)
{
    DiceGUI* dice = dices.at(row).at(nmbr);

    int index = dice->getIndex();
    int value = dice->getValue();

    dice->setIndex(-1);
    dice->setValue(-1);
    dice->disable();
    dice->clear();

    int newRow;
    if(row == 2){
        newRow = player;
    } else {
        newRow = 2;
    }

    for(auto newDice : dices.at(newRow)){
        if(newDice->getValue() == -1){
            dice = newDice;
            break;
        }
    }

    dice->setIndex(index);
    dice->setValue(value);
    dice->setPixmap(diceImages.at(value));
    dice->enable();
}

void MainWindow::initImages()
{
    const string prefix = ":/";
    string fileName;

    for(unsigned int i = 0; i < DICE_IMAGES.size(); ++i){
        fileName = prefix + DICE_IMAGES.at(i);
        QPixmap dice(QString::fromStdString(fileName));

        dice = dice.scaled(DICE_SIZE, DICE_SIZE);
        diceImages.push_back(dice);
    }
}

void MainWindow::initGUI()
{
    DiceGUI* dice;
    vector<DiceGUI*> rowVctr;
    for(int row = 0; row < 3; ++row){
        rowVctr = {};
        for(int nmbr = 0; nmbr < 6; ++nmbr){
            dice = new DiceGUI(row, nmbr, this);

            dice->setGeometry(DICE_ROW_X + nmbr * (DICE_SIZE + DICE_GAP),
                              DICE_ROW_Y.at(row),
                              DICE_SIZE,
                              DICE_SIZE);

            connect(dice, &DiceGUI::buttonPressed, this, &MainWindow::onDiceClicked);

            if(row == 2){
                dice->setPixmap(diceImages.at(nmbr));
                dice->setIndex(nmbr);
                dice->setValue(nmbr);
                dice->enable();
            }

            rowVctr.push_back(dice);
        }
        dices.push_back(rowVctr);
    }
}

// Don't change this
void MainWindow::holdDice(unordered_set<int>& dice)
{
    // eventHandler->createHoldEvent(dice);
    (void)dice;
}

// Don't change this
void MainWindow::saveDice(unordered_set<int>& dice)
{
    // eventHandler->createSaveEvent(dice);
    (void)dice;
}

void MainWindow::on_pushButton_clicked()
{
    // eventHandler->retryConnection();
}
