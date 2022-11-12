#ifndef FRIENDOPERATORLABEL_H
#define FRIENDOPERATORLABEL_H

#include <QLabel>
#include <QWidget>

class FriendOperatorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FriendOperatorLabel(QWidget *parent = nullptr);

signals:
    void friendOperation(QLabel *lbl);
public:
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // ADDREMOVEFRIENDLABEL_H
