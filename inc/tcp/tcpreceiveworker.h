#ifndef TCPRECEIVEWORKER_H
#define TCPRECEIVEWORKER_H

#include <QThread>
#include <QTcpSocket>
#include "settingmessageworker.h"

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
public:
    TCPReceiveWorker(QObject *parent, QTcpSocket *socket);
};

#endif // TCPRECEIVEWORKER_H
