#ifndef TCPRECEIVEWORKER_H
#define TCPRECEIVEWORKER_H

#include <QThread>
#include <QTcpSocket>
#include "settingmessageworker.h"
#include "friendsmessageworker.h"
#include "flushmessageworker.h"

class TCPReceiveWorker: public QObject
{
    Q_OBJECT
signals:
    void registerFail(QString msg);
    void loginFail(QString msg);
public slots:
    void receiveData();
private:
    QTcpSocket *tcp_sock;

    SettingMessageWorker *setting_worker;
    FriendsMessageWorker *friends_worker;
    FlushMessageWorker *flush_worker;
public:
    TCPReceiveWorker(QObject *parent, QTcpSocket *socket);
    void init();
    void startFullFunction();
};

#endif // TCPRECEIVEWORKER_H
