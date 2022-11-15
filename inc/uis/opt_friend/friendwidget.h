#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QStackedWidget>
#include <QHash>
#include <QList>
#include <QVector>
#include <QMutex>
#include "basewidget.h"
#include "friendbriefinfo.h"


namespace Ui {
class FriendWidget;
}

class StackedWidget;
class FriendDetailWidget;
class NewFriendWidget;
class FriendBriefWidget;
class NewFriendBriefWidget;


class FriendWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit FriendWidget(StackedWidget *parent);
    ~FriendWidget();

    void init() override;
private:
    Ui::FriendWidget *ui;

    QPixmap message_img;
    QPixmap friend_img;
    QPixmap group_img;
    QPixmap setting_img;

    StackedWidget *stack_wnd;
    NewFriendWidget *new_frnd_widget;
    FriendDetailWidget *frnd_detail_widget;

    NewFriendBriefWidget *new_brief_wid;
    //用于储存FriendBriefWidget,其中key为账号
    QMap<QString, FriendBriefWidget*> frnds_wnds_map;

    const int wid_index;


    void initOptionLabels();
    void initListWidget();
    void initOtherWidgets();


    QMutex account_frndinfo_map_mutex;
    //由账号找到对应的FriendBriefInfo
    QHash<QString, FriendBriefInfo> account_frndinfo_map;
public slots:
    void newFriendRequireCome();
    void updateFriendsList(FrndInfoVectPtr frnd_info);
public:
    //用于new_brief_wid回复图标
    void allFriendsApplySlove();
    //void storeFriendsInformation(QVector<FriendBriefInfo>& frnd_infos);
    //如果account不在好友列表里，返回无效的FriendBriefInfo
    //这两个函数不考虑自己账号
    FriendBriefInfo getFriendBriefInfo(const QString& account);
    bool isMyFriend(const QString& account);
    void goAheadToThisWidget() override;
};

#endif // FRIENDSWIDGET_H
