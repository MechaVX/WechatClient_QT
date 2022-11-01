#include "inc/tcp/tcpstandardmessage.h"

#include <string.h>

namespace tcp_standard_message
{

QSharedPointer<TCPMessage> TCPMessage::createTCPMessage(MessageType msg_typ, int msg_opt, const std::vector<std::string>& strs)
{
    int size = 0;
    for (const std::string& str: strs)
    {
        size += str.length() + 1;
    }
    QSharedPointer<TCPMessage> msg_stru(new TCPMessage);
    msg_stru->msg_typ = msg_typ;
    msg_stru->msg_opt = msg_opt;
    msg_stru->data_len = size;
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
    *ptr = '\0';
    return msg_stru;
}

TCPMessage::TCPMessage(): data_buf(nullptr) {}

TCPMessage::~TCPMessage()
{
    if (data_buf != nullptr)
        delete data_buf;
}

TCPMessage::TCPMessage(TCPMessage&& msg_stru)
{
    this->data_len = msg_stru.data_len;
    this->msg_typ = msg_stru.msg_typ;
    this->msg_opt = msg_stru.msg_opt;
    this->data_buf = msg_stru.data_buf;
    msg_stru.msg_opt = -1;
    msg_stru.data_buf = nullptr;
}

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

}
