#include "inc/tcp/tcphelper.h"
#include "globaldefine.h"
#include "loginwidget.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QMutexLocker>


TCPMessageHelper::TCPMessageHelper(QObject *parent, TCPHelper *tcp_helper):
    QObject(parent),
    tcp_helper(tcp_helper)
{
    QObject::connect(this, &TCPMessageHelper::sendMessageSignal, tcp_helper, &TCPHelper::commitTCPMessage);
}

bool TCPMessageHelper::commitTCPMessage(TCPMsgStruPtr tcp_msg_stru)
{
    if (tcp_helper == nullptr)
    {
        qDebug() << "TCPMessageHelper::commitTCPMessage: tcp_helper == nullptr";
        return false;
    }
    emit sendMessageSignal(tcp_msg_stru);
    return true;
}

TCPHelper::TCPHelper(QObject *parent): QObject(parent), keep_connecting(false), connected_success(false)
{

}

TCPHelper::~TCPHelper()
{

}

void TCPHelper::prepareToExit()
{
    if (connected_success)
    {
        tcp_socket->disconnectFromHost();
        tcp_socket->close();
    }
}


void TCPHelper::init()
{
    tcp_socket = new QTcpSocket(this);
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &TCPHelper::timeoutReconnect);
    this->beginTCPConnect();
}


void TCPHelper::beginTCPConnect()
{
    //连接设置
    QObject::connect(tcp_socket, &QTcpSocket::connected, this, &TCPHelper::connectSuccessfully);
    QObject::connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectError()));
    tcp_socket->connectToHost(QHostAddress(server_config::server_ip), server_config::server_port);

}

void TCPHelper::timeoutReconnect()
{
    tcp_socket->abort();
    tcp_socket->connectToHost(QHostAddress(server_config::server_ip), server_config::server_port);
}

void TCPHelper::connectSuccessfully()
{
    timer->stop();
    keep_connecting = false;
    connected_success = true;
    send_worker = new TCPSendWorker(this, tcp_socket);
    recv_worker = new TCPReceiveWorker(this, tcp_socket);
    send_worker->init();
    recv_worker->init();
    //QMessageBox::information(dynamic_cast<QWidget*>(this->parent()), "连接成功", "成功连接至服务器!", QMessageBox::Ok);
}

void TCPHelper::connectError()
{
    qDebug() << "TCPHelper::connectError";
    if (!keep_connecting)
    {
        keep_connecting = true;
        //QMessageBox::critical(dynamic_cast<QWidget*>(this->parent()), "连接错误", "无法连接至服务器，请检查网络后重试!");
        timer->start(5000);
    }
}

QTcpSocket* TCPHelper::getTCPSocket()
{
    return tcp_socket;
}


bool TCPHelper::isConnectToServer()
{
    return connected_success;
}

void TCPHelper::completelyStart()
{
    recv_worker->startFullFunction();
}


std::string TCPHelper::serializeString(const QVector<std::string>& str_arr)
{
    //先遍历以减少时间开销
    int total_size = 0;
    for (auto& str: str_arr)
    {
        total_size += str.length();
        ++total_size;
    }
    std::string result;
    result.reserve(total_size);
    for (auto& str: str_arr)
    {
        result += str;
        result.push_back(' ');
    }
    result.pop_back();
    return result;
}

void TCPHelper::commitTCPMessage(TCPMsgStruPtr tcp_msg_stru)
{
    if (!connected_success)
        return;
    send_worker->sendTCPMessage(tcp_msg_stru);
}

/*
//将该结构体的成员以字符串形式发送，接收端无需考虑大小端的问题
bool TCPHelper::commitTCPMessage(QSharedPointer<TCPMessage> tcp_msg_stru)
{
    //if (!connected_success)
        //return false;
    //send_worker->sendTCPMessage(tcp_msg_stru);
    tmp_msg_list_mutex.lock();
    tmp_msg_list.push_back(tcp_msg_stru);
    tmp_msg_list_mutex.unlock();
    return true;
}

void TCPHelper::prepareToSendTCPMessage()
{
    //先将所有消息转移
    tmp_msg_list_mutex.lock();
    if (!tmp_msg_list.empty())
        tmp_msg_list.swap(msg_list);
    tmp_msg_list_mutex.unlock();
    //将所有的消息发送
    for (auto& msg_stru: msg_list)
        send_worker->sendTCPMessage(msg_stru);
    msg_list.clear();
}
*/
