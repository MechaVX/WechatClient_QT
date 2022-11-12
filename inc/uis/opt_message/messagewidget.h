#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QMap>
#include <QListWidgetItem>
#include "communicationmessage.h"
#include "basewidget.h"

namespace Ui {
class MessageWidget;
}

class StackedWidget;
class FriendBriefInfo;
class ListMessageItem;

class MessageWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(StackedWidget *parent);
    ~MessageWidget();

    void init() override;
    void goAheadToThisWidget() override;
    //同时需要frnd_info指明发送者的基本信息
    void newMessageCome(communication_message::Message msg_stru, FriendBriefInfo *frnd_info);
private:
    Ui::MessageWidget *ui;

    QPixmap message_img;
    QPixmap friend_img;
    QPixmap group_img;
    QPixmap setting_img;

    QIcon icon_file;
    QIcon icon_video;
    QIcon icon_image;
    QIcon icon_send;
    QIcon icon_clean;

    const int wid_index;

    StackedWidget *stack_wnd;
    //账号或群组为key,对应的item指针为value
    QMap<QString, ListMessageItem*> account_item_map;

    void initOptionLabels();
    void initCommunicateQuickButtons();

    void addAnWidgetToFront(QListWidget *list_wid, QListWidgetItem *item, QWidget *wnd);

};

#endif // MESSAGEWIDGET_H
