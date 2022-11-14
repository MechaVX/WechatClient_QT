#include "flushmessageworker.h"
#include "friendwidget.h"
#include "globaldefine.h"

#include <QDebug>
#include <QVector>

using namespace tcp_standard_message;
using namespace main_widgets_managing;

FlushMessageWorker::FlushMessageWorker(QObject *parent) : BaseMessageWorker(parent)
{

}

void FlushMessageWorker::init()
{

}

void FlushMessageWorker::startAll()
{
    FriendWidget *frnd_wnd = dynamic_cast<FriendWidget*>(getWidgetPointer(friend_widget));
    QObject::connect(this, &FlushMessageWorker::updateFriends, frnd_wnd, &FriendWidget::updateFriendsList);
}

void FlushMessageWorker::analizeMsgStru(QSharedPointer<TCPMessage> msg_stru)
{
    if (msg_stru->msg_opt == flush_friends)
    {
        flushFriend(msg_stru);
    }

}

void FlushMessageWorker::flushFriend(QSharedPointer<TCPMessage> msg_stru)
{
    //result[0]为好友账户,result[1]为标签，result[2]为昵称，result[3]为用户名，如此循环
    //因为规定了用户的昵称不能带有空格符
    QVector<QString> result = this->splitDataBySpace(msg_stru->data_buf);
    int size = result.size();
    if (size % 4 != 0)
    {
        qDebug() << "\041[36m" << "size= " << size << ",result.size() % 4 != 0";
        for (QString& str: result)
            qDebug() << str;
    }
    FrndInfoVectPtr infos(new QVector<FriendBriefInfo>);
    infos->reserve(size / 4);
    for (int i = 0; i < size; i += 4)
    {
        infos->push_back({ result[i], result[i + 1], result[i + 2], result[i + 3] });
    }
    emit updateFriends(infos);

}
