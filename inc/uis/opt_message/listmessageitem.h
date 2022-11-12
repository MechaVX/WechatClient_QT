#ifndef LISTMESSAGEITEM_H
#define LISTMESSAGEITEM_H

#include <QListWidgetItem>
#include <QTime>
#include <QList>

#include "communicationmessage.h"

class FriendBriefInfo;
class FriendMessageBriefWidget;

class ListMessageItem : public QListWidgetItem
{
public:
    explicit ListMessageItem();
    ~ListMessageItem();

    //生成窗口类，同时绑定至QListWidget
    void init(QListWidget *list_wid, FriendBriefInfo *frnd_info);
    //运算符重载的重写要注意
    bool operator<(const QListWidgetItem& item) const override;

    void receiveNewMessage(const communication_message::Message& msg_stru);

private:
    QListWidget *list_wid;
    FriendBriefInfo *frnd_info;
    FriendMessageBriefWidget *frnd_wnd;
    //储存消息列表
    QList<communication_message::Message> msgs_list;
};

#endif // LISTMESSAGEITEM_H
