#ifndef BASEMESSAGEWORKER_H
#define BASEMESSAGEWORKER_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QSharedPointer>

#include "tcpstandardmessage.h"

using tcp_standard_message::TCPMessage;
using std::string;

class TCPMessageHelper;

//该类的子类用于处理同的消息类型(tcp_standard_message::MessageType)
//对于TCPSenderWorker，只需要本基类即可完成所有功能需求
//对于TCPReceiverWorker，需要派生不同的子类实现不同的功能
class BaseMessageWorker: public QObject
{
    Q_OBJECT
public:
    BaseMessageWorker(QObject *parent);
    string serializeMsgStruToString(const TCPMessage& msg_stru) const;

    virtual void analizeMsgStru(QSharedPointer<TCPMessage> msg_stru);
protected:
    //该函数用于按照空格分割字符串，data_buf中间不能包含'\0'
    virtual QVector<QString> splitDataBySpace(const char *data_buf);
    //如果data_buf中间可能包含'\0'，使用该函数
    virtual QVector<QString> splitDataBySpace(const char *data_buf, int len);

    //对于BaseMessageWorker的子类，构造完成后的启动分为两个过程
    //init是启用最基本的功能，该功能不包括与Widget的相关操作
    //startAll是启动所有功能，包括对Widget的相关connect
    //这样设计是为了确保Widget构造出来后才进行正确的connect
    //virtual void init() = 0;
    //virtual void startAll() = 0;
    TCPMessageHelper *msg_helper;

};

#endif // BASEMESSAGEWORKER_H
