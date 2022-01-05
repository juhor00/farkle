#include "dicegui.h"

DiceGUI::DiceGUI(int diceNmbr):
    diceNmbr(diceNmbr)
{
    this->setFixedSize(SIZE, SIZE);
}

void DiceGUI::disable()
{
    disabled = true;
}

void DiceGUI::enable()
{
    disabled = false;
}

void DiceGUI::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton){
        emit buttonPressed(diceNmbr);
    }
}
