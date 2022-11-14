#include "basemessageworker.h"

#include <QDebug>

BaseMessageWorker::BaseMessageWorker(QObject *parent): QObject(parent)
{
}

QVector<QString> BaseMessageWorker::splitDataBySpace(const char *data_buf)
{
    QVector<QString> result;
    if (data_buf == nullptr)
        return result;
    int beg_index = 0;
    int end_index = 0;
    QString str(data_buf);
    int length = str.length();
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

void BaseMessageWorker::analizeMsgStru(QSharedPointer<TCPMessage> msg_stru)
{

}
