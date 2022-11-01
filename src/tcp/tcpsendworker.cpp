#include "inc/tcp/tcpsendworker.h"


TCPSendWorker::TCPSendWorker(QObject *parent, QTcpSocket *sock): QObject(parent), tcp_sock(sock)
{
    base_msg_worker = new BaseMessageWorker(this);
}



void TCPSendWorker::sendTCPMessage(QSharedPointer<TCPMessage> msg_stru)
{
    string str = base_msg_worker->serializeMsgStruToString(*msg_stru);
    tcp_sock->write(str.data(), str.length());
}


