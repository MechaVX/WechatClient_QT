#ifndef TCPHELPER_H
#define TCPHELPER_H

#include <QTcpSocket>
#include <QTimer>
#include <QWidget>
#include <QVector>
#include <memory>

#include "tcpstandardmessage.h"
#include "tcpsendworker.h"
#include "tcpreceiveworker.h"


class TCPHelper: public QObject
{
    Q_OBJECT
private:
    QTcpSocket *tcp_socket;
    QTimer *timer;

    TCPSendWorker *send_worker;
    TCPReceiveWorker *recv_worker;

    //如果连接不上服务器，会尝试一直连接
    bool keep_connecting;
    bool connected_success;
public:
    TCPHelper(QWidget *parent);
    ~TCPHelper();
    void beginTCPConnect();
    bool isConnectToServer();
    //返回的字符串中结尾数组为'\0'
    std::string serializeString(const QVector<std::string>& str_arr);
    bool commitTCPMessage(QSharedPointer<tcp_standard_message::TCPMessage> tcp_msg_stru);
    QTcpSocket* getTCPSocket();

    //主要考虑到recv_worker的完全启动需要等待其他窗口全都生成，该函数应在其他窗口new生成后再使用
    void completelyStart();
private slots:
    //
    void connectSuccessfully();
    void connectError();
    void timeoutReconnect();
};

#endif // TCPHELPER_H
