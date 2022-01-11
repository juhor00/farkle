#ifndef DICE_H
#define DICE_H

#include <QLabel>
#include <QMouseEvent>


class DiceGUI : public QLabel
{
    Q_OBJECT

public:
    DiceGUI(int row, int index, QWidget* parent);

    void disable();
    void enable();

    void setIndex(int index);
    void setValue(int value);

    int getIndex() const;
    int getValue() const;

signals:
    void buttonPressed(int row, int nmbr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:

    int row_;
    int nmbr_;
    bool enabled = false;

    int index_ = -1;
    int value_ = -1;
};

#endif // DICE_H
