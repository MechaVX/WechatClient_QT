#ifndef SETTINGMESSAGEWORKER_H
#define SETTINGMESSAGEWORKER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "inc/tcp/tcpstandardmessage.h"
#include "inc/tcp/basemessageworker.h"

using tcp_standard_message::TCPMessage;

//该类专门处理tcp_standard_message::message_type为setting的请求
class SettingMessageWorker: public BaseMessageWorker
{
    Q_OBJECT
private:
    //规定返回空字符串表示执行成功
    QString registerNewUser(const char *data_buf);
    void praiseMessageStruct(TCPMessage *msg_stru);
    QTcpSocket *tcp_socket;
public:
    SettingMessageWorker(QObject *parent);
    void init();
    void setTCPSocket(QTcpSocket *sock);
    void analizeMsgStru(QSharedPointer<TCPMessage> msg_stru) override;

signals:
    void registerSignal(bool success, QString msg);
    void loginSignal(bool success, QString msg);
};

#endif // SETTINGMESSAGEWORKER_H
