#include "dice.h"

DiceGUI::DiceGUI(int row, int nmbr, QWidget* parent):
    QLabel(parent), row(row), nmbr(nmbr)
{
}

void DiceGUI::disable()
{
    enabled = false;
}

void DiceGUI::enable()
{
    enabled = true;
}

void DiceGUI::mousePressEvent(QMouseEvent* event)
{
    if(enabled and event->button() == Qt::LeftButton){
        emit buttonPressed(row, nmbr);
    }
}
