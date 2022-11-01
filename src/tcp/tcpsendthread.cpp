#include "inc/tcp/tcpsendthread.h"
#include <QDebug>

TCPSendThread::TCPSendThread(QObject *parent, QTcpSocket *socket): QThread(parent), tcp_sock(socket), running(false)
{
}

void TCPSendThread::run()
{
    //则tcp_worker对象由该线程创建，线程依赖该对象
    tcp_worker = new TCPSendWorker(this, tcp_sock);
    running = true;
    while (running)
    {
        QThread::msleep(100);
        tcp_worker->sendTCPMessage();
    }
}

void TCPSendThread::transmitTCPMessage(QSharedPointer<TCPMessage> msg_stru)
{
    qDebug() << "TCPSendThread::transmitTCPMessage";
   tcp_worker->commitTCPMessage(msg_stru);
}

TCPSendThread::~TCPSendThread()
{
    if (running)
    {
        running = false;
        this->quit();
        this->wait();
    }

}
