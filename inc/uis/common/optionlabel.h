#ifndef OPTIONLABELUI1_H
#define OPTIONLABELUI1_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class OptionLabel : public QLabel
{
    Q_OBJECT
public:
    explicit OptionLabel(QWidget *parent = nullptr);
    void setIndex(int index);

signals:
    void switchOptionSignal(int index);
private:
    int lbl_index;
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // OPTIONLABELUI1_H
