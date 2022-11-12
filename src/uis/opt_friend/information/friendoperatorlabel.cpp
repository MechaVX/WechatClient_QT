#include "friendoperatorlabel.h"
#include "globaldefine.h"
#include "stackedwidget.h"

#include <QLabel>

using namespace main_widgets_managing;

FriendOperatorLabel::FriendOperatorLabel(QWidget *parent): QLabel(parent)
{

}

void FriendOperatorLabel::mousePressEvent(QMouseEvent *ev)
{
    emit friendOperation(this);
}

