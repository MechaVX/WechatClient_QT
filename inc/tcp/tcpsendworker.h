#ifndef TCPSENDWORKER_H
#define TCPSENDWORKER_H

#include <QTcpSocket>
#include <QString>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#include "settingmessageworker.h"

class TCPSendWorker: public QObject
{
    Q_OBJECT
signals:

private:
    QTcpSocket *tcp_sock;
    //对应发送消息，只需要一个基类的即可
    BaseMessageWorker *base_msg_worker;
public:
    TCPSendWorker(QObject *parent, QTcpSocket *socket);

    void init();
    //将消息存放至待发送链表
    void sendTCPMessage(QSharedPointer<TCPMessage>);
};

#endif // TCPSENDWORKER_H
