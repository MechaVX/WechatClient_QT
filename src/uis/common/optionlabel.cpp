#include "optionlabel.h"

#include "stackedwidget.h"
OptionLabel::OptionLabel(QWidget *parent) : QLabel(parent)
{
}

void OptionLabel::setIndex(int index)
{
    this->lbl_index = index;
}


void OptionLabel::mousePressEvent(QMouseEvent *ev)
{
    emit switchOptionSignal(this->lbl_index);
    ev->accept();
}
