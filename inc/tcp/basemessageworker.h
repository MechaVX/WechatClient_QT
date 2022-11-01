#ifndef BASEMESSAGEWORKER_H
#define BASEMESSAGEWORKER_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QSharedPointer>

#include "tcpstandardmessage.h"

using tcp_standard_message::TCPMessage;
using std::string;

class BaseMessageWorker: public QObject
{
    Q_OBJECT
public:
    BaseMessageWorker(QObject *parent);
    string serializeMsgStruToString(const TCPMessage& msg_stru) const;
    void praiseDataToMsgStru(TCPMessage *tcp_msg_stru, const char *recv_data);
    virtual void analizeMsgStru(QSharedPointer<TCPMessage> msg_stru);
protected:

    //该函数用于按照空格分割字符串，data_buf中间不能包含'\0'
    virtual QVector<QString> splitDataBySpace(const char *data_buf);
    //如果data_buf中间可能包含'\0'，使用该函数
    virtual QVector<QString> splitDataBySpace(const char *data_buf, int len);
};

#endif // BASEMESSAGEWORKER_H
