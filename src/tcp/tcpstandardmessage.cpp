#include "tcpstandardmessage.h"
#include "loginwidget.h"

#include <string.h>
#include <QSharedPointer>
#include <ctime>
#include <QTime>
#include <QDebug>

namespace tcp_standard_message
{

const QString TCPMessage::server_account = "00000000000";

QSharedPointer<TCPMessage> TCPMessage::createTCPMessage(
            MessageType msg_typ,
            int msg_opt,
            const QString& sender,
            const QString& receiver,
            const std::vector<std::string>& strs)
{
    QSharedPointer<TCPMessage> msg_stru(new TCPMessage);
    int len1 = sender.length();
    if (len1 != ACCOUNT_LEN)
    {
        qDebug() << "TCPMessage::createTCPMessage receiver error:sender=" << sender;
        return msg_stru;
    }
    int len2 = receiver.length();
    if (len2 != ACCOUNT_LEN)
    {
        qDebug() << "TCPMessage::createTCPMessage receiver error:receiver=" << receiver;
        return msg_stru;
    }
    int size = 0;
    for (const std::string& str: strs)
    {
        size += str.length() + 1;
    }
    msg_stru->msg_typ = msg_typ;
    msg_stru->msg_opt = msg_opt;

    std::string tmp = sender.toStdString();
    for (int i = 0; i < ACCOUNT_LEN; ++i)
    {
        msg_stru->sender[i] = tmp[i];
    }
    tmp = receiver.toStdString();
    for (int i = 0; i < ACCOUNT_LEN; ++i)
    {
        msg_stru->receiver[i] = tmp[i];
    }

    msg_stru->data_len = size;

    if (size == 0)
        return msg_stru;
    msg_stru->data_buf = new char[size];
    char *ptr = msg_stru->data_buf;
    for (const std::string& str: strs)
    {
        for (char c: str)
        {
            *ptr = c;
            ++ptr;
        }
        *ptr = ' ';
        ++ptr;
    }
    --ptr;
    *ptr = '\0';
    return msg_stru;
}

TCPMessage::TCPMessage(): data_buf(nullptr)
{
    this->timestamp = (quint32)time(0);
    this->sender[ACCOUNT_LEN] = '\0';
    this->receiver[ACCOUNT_LEN] = '\0';
}

TCPMessage::~TCPMessage()
{
    if (data_buf != nullptr)
        delete data_buf;
}
/*
TCPMessage::TCPMessage(const TCPMessage& other)
{
    this->data_len = other.data_len;
    this->msg_typ = other.msg_typ;
    this->msg_opt = other.msg_opt;
    this->timestamp = msg_stru.timestamp;
    for (int i = 0; i < ACCOUNT_LEN; ++i)
    {
        this->sender[i] = msg_stru.sender[i];
        this->receiver[i] = msg_stru.receiver[i];
    }
    if (other.data_buf != nullptr)
    {
        this->data_buf = new char[data_len];
        for (uint32_t i = 0; i < data_len; ++i)
            data_buf[i] = other.data_buf[i];
    }
    else
    {
        this->data_buf = nullptr;
    }
}
*/
TCPMessage::TCPMessage(TCPMessage&& msg_stru)
{
    this->msg_typ = msg_stru.msg_typ;
    this->msg_opt = msg_stru.msg_opt;
    this->timestamp = msg_stru.timestamp;
    for (int i = 0; i < ACCOUNT_LEN; ++i)
    {
        this->sender[i] = msg_stru.sender[i];
        this->receiver[i] = msg_stru.receiver[i];
    }
    this->data_len = msg_stru.data_len;
    this->data_buf = msg_stru.data_buf;
    msg_stru.msg_opt = -1;
    msg_stru.data_buf = nullptr;
}
/*
TCPMessage& TCPMessage::operator=(const TCPMessage& other)
{
    this->data_len = other.data_len;
    this->msg_typ = other.msg_typ;
    this->msg_opt = other.msg_opt;
    if (this->data_buf != nullptr)
        delete data_buf;
    if (other.data_buf != nullptr)
    {
        this->data_buf = new char[data_len];
        for (uint32_t i = 0; i < data_len; ++i)
            data_buf[i] = other.data_buf[i];
    }
    else
    {
        this->data_buf = nullptr;
    }
    return *this;
}
*/
void TCPMessage::copyDataFromString(const std::string& str)
{
    if (data_buf != nullptr)
    {
        delete data_buf;
        data_buf = nullptr;
        this->data_len = 0;
    }
    if (str == "")
        return;
    this->data_len = str.length() + 1;
    data_buf = new char[data_len];
    strcpy(data_buf, str.data());
}

std::string TCPMessage::serializeToStdString() const
{
    std::string result;
    result.reserve(sizeof(TCPMessage) + 6);
    result += std::to_string(timestamp) + ' ';
    result += std::to_string(msg_typ) + ' ';
    result += std::to_string(msg_opt) + ' ';
    for (char c: sender)
        result.push_back(c);
    result.push_back(' ');
    for (char c: receiver)
        result.push_back(c);
    result.push_back(' ');
    result += std::to_string(data_len) + ' ';
    for (uint32_t i = 0; i < data_len; ++i)
    {
        result.push_back(data_buf[i]);
    }
    return result;
}

}
