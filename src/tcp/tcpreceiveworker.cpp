#include "inc/tcp/tcpreceiveworker.h"

#include <QDebug>
#include <QSharedPointer>

TCPReceiveWorker::TCPReceiveWorker(QObject *parent_, QTcpSocket *socket): QObject(parent_), tcp_sock(socket)
{

}

void TCPReceiveWorker::init()
{
    QObject::connect(tcp_sock, &QTcpSocket::readyRead, this, &TCPReceiveWorker::receiveData);

    setting_worker = new SettingMessageWorker(this);
    friends_worker = new FriendsMessageWorker(this);
    flush_worker = new FlushMessageWorker(this);
    setting_worker->init();
    friends_worker->init();
    flush_worker->init();
}

void TCPReceiveWorker::startFullFunction()
{
    setting_worker->startAll();
    friends_worker->startAll();
    flush_worker->startAll();

}

void TCPReceiveWorker::receiveData()
{
    QByteArray recv_data = tcp_sock->readAll();
    QSharedPointer<TCPMessage> msg_stru(new TCPMessage);
    setting_worker->praiseDataToMsgStru(msg_stru.data(), recv_data.data());

    if (msg_stru->msg_typ == tcp_standard_message::setting)
    {
        setting_worker->analizeMsgStru(msg_stru);
    }
    else if (msg_stru->msg_typ == tcp_standard_message::friends)
    {
        friends_worker->analizeMsgStru(msg_stru);
    }
    else if (msg_stru->msg_typ == tcp_standard_message::flush)
    {
        flush_worker->analizeMsgStru(msg_stru);
    }

}


