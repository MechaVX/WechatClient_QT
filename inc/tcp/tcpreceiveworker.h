#ifndef TCPRECEIVEWORKER_H
#define TCPRECEIVEWORKER_H

#include <QThread>
#include <QTcpSocket>
#include "settingmessageworker.h"
#include "friendsmessageworker.h"
#include "flushmessageworker.h"

class TCPReceiveWorker: public QObject
{
    Q_OBJECT
signals:
    void registerFail(QString msg);
    void loginFail(QString msg);
public slots:
    void receiveData();
private:
    QTcpSocket *tcp_sock;

    SettingMessageWorker *setting_worker;
    FriendsMessageWorker *friends_worker;
    FlushMessageWorker *flush_worker;

    QList<TCPMsgStruPtr> praiseDataToMsgStru(const char *recv_data, int data_len);

    //为了解决TCP粘包的问题，如果判断某个socket的消息未发送完毕，先将消息使用储存至此
    QVector<char> incomplete_data;
public:
    TCPReceiveWorker(QObject *parent, QTcpSocket *socket);
    void init();
    void startFullFunction();
};

#endif // TCPRECEIVEWORKER_H
