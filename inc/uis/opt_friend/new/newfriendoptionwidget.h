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

    void init(const QString& frnd_account, const QString& user_name, const QString& message);
    //相同账号的申请还未被处理再次收到该账号的申请
    void flushApplyMessage(const QString& message);
private:
    Ui::NewFriendOptionWidget *ui;

    QPixmap frnd_img;
    QString account;
    QString nickname;
    QString message;

    TCPMessageHelper *msg_helper;
};

#endif // NEWFRIENDOPTIONWIDGET_H
