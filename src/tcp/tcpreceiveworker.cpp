#include "inc/tcp/tcpreceiveworker.h"

#include <QDebug>
#include <QSharedPointer>
#include <QQueue>

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
    auto msg_strus = praiseDataToMsgStru(recv_data.data(), recv_data.length());
    for (auto& msg_stru: msg_strus)
    {
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
}

QList<TCPMsgStruPtr> TCPReceiveWorker::praiseDataToMsgStru(const char *recv_data, int data_len)
{
    QList<TCPMsgStruPtr> result;
    //这里需要循环处理接收的数据
    QQueue<char> datas;

    if (!incomplete_data.empty())
    {
        for (char c: incomplete_data)
            datas.push_back(c);
        incomplete_data.clear();

    }

    for (int i = 0; i < data_len; ++i)
    {
        datas.push_back(recv_data[i]);
    }

    string str_data;
    char c;
    while (!datas.empty())
    {
        while (!datas.empty())
        {
            c = datas.front();
            datas.pop_front();
            if (c == ' ')
                break;
            str_data.push_back(c);
        }
        //说明数据接收不全，则放置incomplete_data中，等待下次与新数据合并处理
        if (datas.empty())
        {
            for (char c: str_data)
                incomplete_data.push_back(c);
            return std::move(result);
        }
        TCPMsgStruPtr tcp_msg_stru(new TCPMessage);
        tcp_msg_stru->msg_typ = (tcp_standard_message::MessageType)stoi(str_data);
        str_data.clear();

        while (!datas.empty())
        {
            c = datas.front();
            datas.pop_front();
            if (c == ' ')
                break;
            str_data.push_back(c);
        }
        //说明数据接收不全，则放置incomplete_data中，等待下次与新数据合并处理
        if (datas.empty())
        {
            str_data = std::to_string(tcp_msg_stru->msg_typ) + ' ' + str_data;
            for (char c: str_data)
                incomplete_data.push_back(c);
            return std::move(result);
        }

        tcp_msg_stru->msg_opt = (tcp_standard_message::MessageType)stoi(str_data);
        str_data.clear();

        while (!datas.empty())
        {
            c = datas.front();
            datas.pop_front();
            if (c == ' ')
                break;
            str_data.push_back(c);
        }
        //说明数据接收不全，则放置incomplete_data中，等待下次与新数据合并处理
        if (datas.empty() && str_data != "0" /* 考虑数据长度为0的情况，此时应是接收完毕*/)
        {
            str_data = std::to_string(tcp_msg_stru->msg_typ) + ' ' + std::to_string(tcp_msg_stru->msg_opt) + ' ' + str_data;
            for (char c: str_data)
                incomplete_data.push_back(c);
            return std::move(result);
        }

        tcp_msg_stru->data_len = (tcp_standard_message::MessageType)stoi(str_data);
        str_data.clear();

        uint32_t size = datas.size();
        if (size < tcp_msg_stru->data_len)
        {
            //接收不全
            string tmp = std::to_string(tcp_msg_stru->msg_typ) + ' ' + std::to_string(tcp_msg_stru->msg_opt) + ' ';
            tmp += std::to_string(tcp_msg_stru->data_len) + ' ';
            while (!datas.empty())
            {
                tmp.push_back(datas.front());
                datas.pop_front();
            }
            for (char c: str_data)
                incomplete_data.push_back(c);
            return std::move(result);
        }
        if (tcp_msg_stru->data_len > 0)
        {
            tcp_msg_stru->data_buf = new char[tcp_msg_stru->data_len];
            for (uint32_t i = 0; i < tcp_msg_stru->data_len; ++i)
            {
                tcp_msg_stru->data_buf[i] = datas.front();
                datas.pop_front();
            }
        }
        result.push_back(tcp_msg_stru);
    }
    return std::move(result);
}


