#ifndef FRIENDSMESSAGEWORKER_H
#define FRIENDSMESSAGEWORKER_H

#include <QTcpSocket>
#include <QSharedPointer>
#include "basemessageworker.h"

class StackedWidget;

class FriendsMessageWorker : public BaseMessageWorker
{
    Q_OBJECT
public:
    explicit FriendsMessageWorker(QObject *parent = nullptr);

    void init();
    void startAll();
    void setTCPSocket(QTcpSocket *sock);
    void analizeMsgStru(QSharedPointer<TCPMessage> msg_stru);
signals:
    void userInfoFound(const QString& account,
                      const QString& user_name,
                      const QString& nick_name,
                      const QString& label,
                      bool is_friend);
    void userInfoNoFound(const QString& account);
    //这个信号是在NewFriendWidget新加好友申请信息的
    void friendApplication(const QString& account, const QString& apply_msg);
    //这个信号是在friendwidget更新显示有好友申请的图标
    void friendApplication();
private:
    QTcpSocket *tcp_socket;

    StackedWidget *stack_wnd;

};

#endif // FRIENDSMESSAGEWORKER_H
