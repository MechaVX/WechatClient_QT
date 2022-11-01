#ifndef TCPRECEIVETHREAD_H
#define TCPRECEIVETHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "inc/tcp/tcpreceiveworker.h"

class TCPReceiveThread: public QThread
{
    Q_OBJECT
signals:

private slots:

public:

    TCPReceiveThread(QObject *parent, QTcpSocket *socket);
    ~TCPReceiveThread();
protected:
    void run() override;
private:
    TCPReceiveWorker *tcp_worker;
    bool running;
    QTcpSocket *tcp_sock;
};

#endif // TCPRECEIVETHREAD_H
