#ifndef TCPHELPER_H
#define TCPHELPER_H

#include <QTcpSocket>
#include <QTimer>
#include <QWidget>
#include <QVector>
#include <QList>
#include <QMutex>

#include "tcpstandardmessage.h"
#include "tcpsendworker.h"
#include "tcpreceiveworker.h"

class TCPHelper;

//该对象提供方法，供发送TCPMessage，需要发送tcp消息，则要使用该类
class TCPMessageHelper: public QObject
{
    Q_OBJECT
private:
    TCPHelper *tcp_helper;
signals:
    //此信号将提醒tcp线程发送消息
    void sendMessageSignal(TCPMsgStruPtr msg_stru);
public:
    TCPMessageHelper(QObject *parent, TCPHelper *tcp_helper);
    bool commitTCPMessage(TCPMsgStruPtr tcp_msg_stru);

};

class TCPHelper: public QObject
{
    Q_OBJECT
    friend class TCPMessageHelper;
private:
    QTcpSocket *tcp_socket;
    QTimer *timer;

    TCPSendWorker *send_worker;
    TCPReceiveWorker *recv_worker;

    /*
    //其他线程将消息暂存至此
    QList<QSharedPointer<TCPMessage> > tmp_msg_list;
    QMutex tmp_msg_list_mutex;
    //这里的消息将全部从tmp_msg_list.swap转移至此
    QList<QSharedPointer<TCPMessage> > msg_list;
    */

    //如果连接不上服务器，会尝试一直连接
    bool keep_connecting;
    bool connected_success;
    int iiii = 4;
public slots:
    void init();
    //主要考虑到recv_worker的完全启动需要等待其他窗口全都生成，该函数应在其他窗口new生成后再使用
    void completelyStart();
    void prepareToExit();
public:
    TCPHelper(QObject *parent = nullptr);
    ~TCPHelper();

    void beginTCPConnect();
    bool isConnectToServer();
    //返回的字符串中结尾数组为'\0'
    std::string serializeString(const QVector<std::string>& str_arr);

    QTcpSocket* getTCPSocket();


private:
    //bool commitTCPMessage(QSharedPointer<tcp_standard_message::TCPMessage> tcp_msg_stru);
    //
private slots:
    //
    void connectSuccessfully();
    void connectError();
    void timeoutReconnect();
    //void prepareToSendTCPMessage();
    void commitTCPMessage(TCPMsgStruPtr tcp_msg_stru);
};



#endif // TCPHELPER_H
