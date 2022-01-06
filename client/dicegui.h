#ifndef DICEGUI_H
#define DICEGUI_H

#include <QLabel>
#include <QMouseEvent>


class DiceGUI : public QLabel
{
    Q_OBJECT

public:
    DiceGUI(int row, int index, QWidget* parent);

    void disable();
    void enable();

signals:
    void buttonPressed(int row, int nmbr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:

    int row;
    int nmbr;
    bool enabled = false;
};

#endif // DICEGUI_H
