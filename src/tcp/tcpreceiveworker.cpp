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
    //timestamp,msg_typ,msg_opt,sender,receiver,data_len

    while (!datas.empty())
    {
        string strs[6];
        char c;
        int index = 0;
        //如果接收到的数据不完整，返回false
        auto analizeDatas = [&]()
        {
            while (!datas.empty())
            {
                c = datas.front();
                datas.pop_front();
                if (c == ' ')
                    break;
                strs[index].push_back(c);
            }
            if (c != ' ')
            {
                //说明数据接收不全，则放置incomplete_data中，等待下次与新数据合并处理
                for (int i = 0; i < index; ++i)
                {
                    for (char c: strs[i])
                        incomplete_data.push_back(c);
                    incomplete_data.push_back(' ');
                }
                for (char c: strs[index])
                    incomplete_data.push_back(c);
                return false;
            }
            return true;
        };

        TCPMsgStruPtr tcp_msg_stru(new TCPMessage);

        if (!analizeDatas())
            return std::move(result);
        tcp_msg_stru->timestamp = (tcp_standard_message::MessageType)stoi(strs[index]);
        ++index;

        if (!analizeDatas())
            return std::move(result);
        tcp_msg_stru->msg_typ = (tcp_standard_message::MessageType)stoi(strs[index]);
        ++index;

        if (!analizeDatas())
            return std::move(result);
        tcp_msg_stru->msg_opt = stoi(strs[index]);
        ++index;

        if (!analizeDatas())
            return std::move(result);
        for (int i = 0; i < ACCOUNT_LEN; ++i)
            tcp_msg_stru->sender[i] = strs[index][i];
        ++index;

        if (!analizeDatas())
            return std::move(result);
        for (int i = 0; i < ACCOUNT_LEN; ++i)
            tcp_msg_stru->receiver[i] = strs[index][i];
        ++index;

        if (!analizeDatas())
            return std::move(result);
        tcp_msg_stru->data_len = stoi(strs[index]);


        //说明数据接收不全，则放置incomplete_data中，等待下次与新数据合并处理
        if (datas.size() < tcp_msg_stru->data_len)
        {
            for (string& str: strs)
            {
                for (char c: str)
                {
                    incomplete_data.push_back(c);
                }
                incomplete_data.push_back(' ');
            }
            while (!datas.empty())
            {
                incomplete_data.push_back(datas.front());
                datas.pop_front();
            }
            return std::move(result);
        }
        if (tcp_msg_stru->data_len > 0)
        {
            tcp_msg_stru->data_buf = new char[tcp_msg_stru->data_len];
            for (quint32 i = 0; i < tcp_msg_stru->data_len; ++i)
            {
                tcp_msg_stru->data_buf[i] = datas.front();
                datas.pop_front();
            }
        }
        result.push_back(tcp_msg_stru);
    }
    return std::move(result);
}


