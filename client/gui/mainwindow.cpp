#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    // eventHandler(new EventHandler(this))
{
    ui->setupUi(this);

    this->setMinimumWidth(WIN_MIN_W);
    this->setMinimumHeight(WIN_MIN_H);
    this->setGeometry(0, 0, 1600, 900);
    //this->setFixedSize(WINDOW_W, WINDOW_H);

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
        newRow = 0;
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
    dice->setPixmap(diceImages.at(value).scaledToWidth(diceSize));
    dice->enable();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    resizeGUI();
}

void MainWindow::scaleW(int& variable, int basevalue)
{
    variable = basevalue * winW / WIN_NORMAL_W;
}

void MainWindow::scaleH(int& variable, int basevalue)
{
    variable = basevalue * winH / WIN_NORMAL_H;
}

void MainWindow::resizeGUI()
{
    winW = this->width();
    winH = this->height();

    if(winW * 9 < winH * 16){
        scaleW(diceSize, DICE_SIZE);
    } else {
        scaleH(diceSize, DICE_SIZE);
    }

    scaleW(diceRowX, DICE_ROW_X);
    scaleW(diceGap, DICE_GAP);

    int i = 0;
    for(auto& h : diceRowY){
        scaleH(h, DICE_ROW_Y.at(i));
        ++i;
    }

    drawGUI();
}

void MainWindow::drawGUI()
{
    DiceGUI* dice;
    for(int row = 0; row < 3; ++row){
        for(int nmbr = 0; nmbr < 6; ++nmbr){
            dice = dices.at(row).at(nmbr);

            dice->setGeometry(diceRowX + nmbr * (diceSize + diceSize),
                              diceRowY.at(row),
                              diceSize,
                              diceSize);

            if(not dice->pixmap().isNull()){
                QPixmap pic = diceImages.at(dice->getValue());
                dice->setPixmap(pic.scaledToWidth(diceSize));
            }
        }
    }
}

void MainWindow::initImages()
{
    const string prefix = ":/";
    string fileName;

    for(unsigned int i = 0; i < DICE_IMAGES.size(); ++i){
        fileName = prefix + DICE_IMAGES.at(i);
        QPixmap dice(QString::fromStdString(fileName));

        dice = dice.scaled(diceSize, diceSize);
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

            connect(dice, &DiceGUI::buttonPressed, this, &MainWindow::onDiceClicked);

            if(row == 2){
                dice->setPixmap(diceImages.at(nmbr).scaledToWidth(diceSize));
                dice->setIndex(nmbr);
                dice->setValue(nmbr);
                dice->enable();
            }

            rowVctr.push_back(dice);
        }
        dices.push_back(rowVctr);
    }

    rollDice = new QPushButton(this);

    resizeGUI();
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
