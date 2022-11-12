#include "messageiconslabel.h"

#include <QDebug>

MessageIconsLabel::MessageIconsLabel(QWidget *parent) : QLabel(parent)
{

}

void MessageIconsLabel::markIconFunciton(msg_icon_attr::IconFunction fun_typ)
{
    this->icon_fun = fun_typ;
}

void MessageIconsLabel::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "MessageIconsLabel::mousePressEvent";
    if (icon_fun == msg_icon_attr::send)
    {
        qDebug() << "send";
    }
    else if (icon_fun == msg_icon_attr::clean)
    {
        qDebug() << "clean";
    }
    else if (icon_fun == msg_icon_attr::file)
    {
        qDebug() << "file";
    }
    else if (icon_fun == msg_icon_attr::video)
    {
        qDebug() << "video";
    }
    else if (icon_fun == msg_icon_attr::image)
    {
        qDebug() << "image";
    }
    ev->accept();
}
