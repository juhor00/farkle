#include "dice.h"

DiceGUI::DiceGUI(int row, int nmbr, QWidget* parent):
    QLabel(parent), row_(row), nmbr_(nmbr)
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

void DiceGUI::setIndex(int index)
{
    index_ = index;
}

void DiceGUI::setValue(int value)
{
    value_ = value;
}

int DiceGUI::getIndex() const
{
    return index_;
}
int DiceGUI::getValue() const
{
    return value_;
}

void DiceGUI::mousePressEvent(QMouseEvent* event)
{
    if(enabled and event->button() == Qt::LeftButton){
        emit buttonPressed(row_, nmbr_);
    }
}
