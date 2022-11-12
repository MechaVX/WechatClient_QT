#ifndef MESSAGEICONSLABEL_H
#define MESSAGEICONSLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

namespace msg_icon_attr
{
enum IconFunction
{
    invalid,
    file,
    video,
    image,
    send,
    clean,
};
}

class MessageIconsLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MessageIconsLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
signals:
private:
    msg_icon_attr::IconFunction icon_fun;
public:
    void markIconFunciton(msg_icon_attr::IconFunction fun_typ);
};

#endif // MESSAGEICONSLABEL_H
