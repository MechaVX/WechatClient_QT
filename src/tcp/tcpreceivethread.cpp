#include "inc/tcp/tcpreceivethread.h"




TCPReceiveThread::TCPReceiveThread(QObject *parent, QTcpSocket *socket): QThread(parent), tcp_sock(socket), running(false)
{
    tcp_worker = new TCPReceiveWorker(this, socket);
}

TCPReceiveThread::~TCPReceiveThread()
{
    if (running)
    {
        running = false;
        this->quit();
        this->wait();
    }

}

void TCPReceiveThread::run()
{
    QObject::connect(tcp_sock, &QTcpSocket::readyRead, tcp_worker, &TCPReceiveWorker::receiveData);
    running = true;
    while (running)
    {
        QThread::msleep(100);
    }
    qDebug() << "receive thread exit";
}
