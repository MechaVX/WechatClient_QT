#include "inc/tcp/settingmessageworker.h"
#include "loginwidget.h"

#include <QDebug>
#include <QMessageBox>

SettingMessageWorker::SettingMessageWorker(QObject *parent): BaseMessageWorker(parent)
{

}


void SettingMessageWorker::analizeMsgStru(QSharedPointer<TCPMessage> msg_stru)
{
    int opt = msg_stru->msg_opt;
    QString str(msg_stru->data_buf);
    bool success = !str.contains("fail");
    if (opt == tcp_standard_message::user_register)
    {
        emit registerSignal(success, str);
    }
    else if (opt == tcp_standard_message::user_login)
    {
        emit loginSignal(success, str);
    }
}

void SettingMessageWorker::init()
{
    LoginWidget *login_widget = dynamic_cast<LoginWidget*>(this->parent()->parent()->parent());
    if (login_widget == nullptr)
    {
        qDebug() << "SettingMessageWorker::SettingMessageWorker dynamic_cast error";
        throw 9;
    }
    QObject::connect(this, &SettingMessageWorker::registerSignal, login_widget, &LoginWidget::userRegisterSlot);
    QObject::connect(this, &SettingMessageWorker::loginSignal, login_widget, &LoginWidget::userLoginSlot);
}

void SettingMessageWorker::startAll()
{

}

void SettingMessageWorker::setTCPSocket(QTcpSocket *sock)
{
    this->tcp_socket = sock;
}
