#ifndef DICEGUI_H
#define DICEGUI_H

#include "mainwindow.h"
#include <QLabel>
#include <QMouseEvent>


class DiceGUI : public QLabel
{
    Q_OBJECT

public:
    DiceGUI(int diceNmbr);

    void disable();
    void enable();

signals:
    void buttonPressed(int diceNmbr);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

private:

    const int SIZE = 100;

    int diceNmbr;
    bool disabled = true;
};

#endif // DICEGUI_H
