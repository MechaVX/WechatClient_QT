#include "friendsmessageworker.h"
#include "loginwidget.h"
#include "stackedwidget.h"
#include "frienddetailwidget.h"
#include "newfriendwidget.h"
#include "friendwidget.h"
#include "tcphelper.h"
#include "globaldefine.h"

using namespace main_widgets_managing;

FriendsMessageWorker::FriendsMessageWorker(QObject *parent) : BaseMessageWorker(parent)
{

}

void FriendsMessageWorker::init()
{

}

void FriendsMessageWorker::startAll()
{
    msg_helper = new TCPMessageHelper(this, dynamic_cast<LoginWidget*>(getWidgetPointer(login_widget))->getTCPHelper());

    FriendDetailWidget *frnd_det_wnd = dynamic_cast<FriendDetailWidget*>(getWidgetPointer(friend_detail_widget));

    void (FriendDetailWidget::*fun)(const QString&, const QString&, const QString&, const QString&, bool) = &FriendDetailWidget::showUserInformation;

    QObject::connect(this, &FriendsMessageWorker::userInfoFound, frnd_det_wnd, fun);
    QObject::connect(this, &FriendsMessageWorker::userInfoNoFound, frnd_det_wnd, &FriendDetailWidget::showUserNoFound);

    void (FriendsMessageWorker::*fun1)(const QString&, const QString&) = &FriendsMessageWorker::friendApplication;
    NewFriendWidget *new_frnd_wnd = dynamic_cast<NewFriendWidget*>(getWidgetPointer(new_friend_widget));
    QObject::connect(this, fun1, new_frnd_wnd, &NewFriendWidget::newFriendApplyCome);

    void (FriendsMessageWorker::*fun2)() = &FriendsMessageWorker::friendApplication;
    FriendWidget *frnd_wnd = dynamic_cast<FriendWidget*>(getWidgetPointer(friend_widget));
    QObject::connect(this, fun2, frnd_wnd, &FriendWidget::newFriendRequireCome);
}


void FriendsMessageWorker::setTCPSocket(QTcpSocket *sock)
{
    this->tcp_socket = sock;
}

using namespace tcp_standard_message;

void FriendsMessageWorker::analizeMsgStru(QSharedPointer<TCPMessage> msg_stru)
{
    auto result = this->splitDataBySpace(msg_stru->data_buf);
    int opt = msg_stru->msg_opt;
    if (opt == tcp_standard_message::search_someone)
    {
        //如果找到该用户，result[0]为账户，result[1]为用户名
        //如果找不到,result[0]="fail.",result[1]="user",result[2]=account || result[2]=phone,result[3]="no",result[4]="found."
        if (msg_stru->data_buf[0] != 'f')
        {
            //data_buf!="fail. account no found!"
            emit userInfoFound(result[0], result[1], QString(), QString(), false);
        }
        else
        {
            emit userInfoNoFound(result[2]);
        }

    }
    else if (opt == tcp_standard_message::add_friend)
    {
        //result[0]为申请留言信息
        auto result = this->splitDataBySpace(msg_stru->data_buf);

        QString apply_msg(msg_stru->data_buf);

        emit friendApplication(msg_stru->sender, apply_msg);
        emit friendApplication();
    }
    else if (opt == tcp_standard_message::agree_add_friend)
    {
        qDebug() << "agree add friend" << msg_stru->data_buf;
        StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));
        //重新刷新好友列表
        msg_stru = TCPMessage::createTCPMessage(tcp_standard_message::flush, flush_friends, stack_wnd->getAccount());
        msg_helper->commitTCPMessage(msg_stru);
    }
    else if (opt == tcp_standard_message::send_message)
    {

    }

}
