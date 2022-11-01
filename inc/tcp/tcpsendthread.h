#ifndef TCPSENDTHREAD_H
#define TCPSENDTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "tcpsendworker.h"


class TCPSendThread: public QThread
{
    Q_OBJECT
public:
    TCPSendThread(QObject *parent, QTcpSocket *socket);
    ~TCPSendThread();
    void transmitTCPMessage(QSharedPointer<TCPMessage> msg_stru);
    void stopThread();
protected:
    void run() override;
private:
    QTcpSocket *tcp_sock;
    TCPSendWorker *tcp_worker;

    bool running;
};

#endif // TCPSENDTHREAD_H
