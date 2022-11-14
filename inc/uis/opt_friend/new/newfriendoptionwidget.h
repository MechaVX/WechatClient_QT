#ifndef NEWFRIENDOPTIONWIDGET_H
#define NEWFRIENDOPTIONWIDGET_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class NewFriendOptionWidget;
}

class TCPMessageHelper;

class NewFriendOptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewFriendOptionWidget(QWidget *parent = nullptr);
    ~NewFriendOptionWidget();

    void init(const QString& account, const QString& user_name, const QString& message);

private:
    Ui::NewFriendOptionWidget *ui;

    QPixmap frnd_img;
    QString account;
    QString nickname;
    QString message;

    TCPMessageHelper *msg_helper;
};

#endif // NEWFRIENDOPTIONWIDGET_H
