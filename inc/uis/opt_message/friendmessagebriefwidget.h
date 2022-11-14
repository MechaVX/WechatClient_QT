#ifndef FRIENDMESSAGEBRIEFWIDGET_H
#define FRIENDMESSAGEBRIEFWIDGET_H

#include <QWidget>
#include <QList>
#include "friendbriefinfo.h"
#include "communicationmessage.h"

namespace Ui {
class FriendMessageBriefWidget;
}



class FriendMessageBriefWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FriendMessageBriefWidget(QWidget *parent = nullptr);
    ~FriendMessageBriefWidget();

    void init(const FriendBriefInfo& frnd_info);

    void flushMessageDisplay(const communication_message::Message& msg_stru);

protected:
    //返回true表示事件处理完毕，不会再传播
    bool event(QEvent *ev) override;

    void mousePressEvent(QMouseEvent *event) override;
private:


    Ui::FriendMessageBriefWidget *ui;
    //记录对方的基本信息
    FriendBriefInfo frnd_info;

};

#endif // BRIEFVIEWSMALLWIDGET_H
