#include "inc/tcp/basemessageworker.h"

BaseMessageWorker::BaseMessageWorker(QObject *parent): QObject(parent) {}

QVector<QString> BaseMessageWorker::splitDataBySpace(const char *data_buf)
{
    int beg_index = 0;
    int end_index = 0;
    QString str(data_buf);

    int length = str.length();
    QVector<QString> result;
    while (end_index < length)
    {
        while (str[end_index] != ' ' && end_index < length)
            ++end_index;
        result.push_back(str.toStdString().substr(beg_index, end_index - beg_index).data());
        ++end_index;
        beg_index = end_index;
    }
    return std::move(result);
}

QVector<QString> BaseMessageWorker::splitDataBySpace(const char *data_buf, int len)
{

}

string BaseMessageWorker::serializeMsgStruToString(const TCPMessage& msg_stru) const
{
    string result;
    result += std::to_string(msg_stru.msg_typ) + ' ';
    result += std::to_string(msg_stru.msg_opt) + ' ';
    result += std::to_string(msg_stru.data_len) + ' ';
    for (quint32 i = 0; i < msg_stru.data_len; ++i)
    {
        result.push_back(msg_stru.data_buf[i]);
    }
    return result;
}

void BaseMessageWorker::praiseDataToMsgStru(TCPMessage *tcp_msg_stru, const char *recv_data)
{
    int end_index = 0;
    int beg_index = 0;
    std::string str_data = recv_data;
    while (str_data[end_index] != ' ')
        ++end_index;
    tcp_msg_stru->msg_typ = (tcp_standard_message::MessageType)stoi(str_data.substr(beg_index, end_index - beg_index));
    ++end_index;
    beg_index = end_index;
    while (str_data[end_index] != ' ')
        ++end_index;
    tcp_msg_stru->msg_opt = stoi(str_data.substr(beg_index, end_index - beg_index));

    ++end_index;
    beg_index = end_index;
    while (str_data[end_index] != ' ')
        ++end_index;
    tcp_msg_stru->data_len = stoi(str_data.substr(beg_index, end_index - beg_index));

    tcp_msg_stru->data_buf = new char[tcp_msg_stru->data_len];
    for (quint32 index = end_index + 1, count = 0; count < tcp_msg_stru->data_len; ++count, ++index)
    {
        tcp_msg_stru->data_buf[count] = recv_data[index];
    }
}

void BaseMessageWorker::analizeMsgStru(QSharedPointer<TCPMessage> msg_stru)
{

}
