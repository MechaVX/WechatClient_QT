#include "friendwidget.h"
#include "ui_friendwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "optionlabel.h"
#include "friendbriefwidget.h"
#include "newfriendbriefwidget.h"
#include "newfriendwidget.h"
#include "frienddetailwidget.h"
#include "globaldefine.h"

#include <QListWidget>
#include <QDebug>
#include <QMutexLocker>

using namespace images_sources;

FriendWidget::FriendWidget(StackedWidget *parent) :
    BaseWidget(main_widgets_managing::friend_widget, parent),
    ui(new Ui::FriendWidget),
    message_img(uis_opt_message_dis),
    friend_img(uis_opt_friend_ena),
    group_img(uis_opt_group_dis),
    setting_img(uis_opt_setting_dis),
    wid_index(1)
{
    ui->setupUi(this);

    this->stack_wnd = dynamic_cast<StackedWidget*>(parent);

    ui->search_button->setIcon(QIcon(uis_search));
    ui->search_button->setFlat(true);
    ui->search_button->setStyleSheet("border: 0px");


}

FriendWidget::~FriendWidget()
{
    delete ui;
}

void FriendWidget::init()
{
    initOptionLabels();
    initListWidget();
    initOtherWidgets();

}

void FriendWidget::initOptionLabels()
{
    ui->message_lbl->setPixmap(message_img);
    ui->friend_lbl->setPixmap(friend_img);
    ui->group_lbl->setPixmap(group_img);
    ui->setting_lbl->setPixmap(setting_img);

    ui->message_lbl->setIndex(0);
    ui->friend_lbl->setIndex(1);
    ui->group_lbl->setIndex(2);
    ui->setting_lbl->setIndex(3);

    void (StackedWidget::*swt_fun)(int) = &StackedWidget::switchWidget;
    QObject::connect(ui->message_lbl, &OptionLabel::switchOptionSignal, stack_wnd, swt_fun);
    QObject::connect(ui->friend_lbl, &OptionLabel::switchOptionSignal, stack_wnd, swt_fun);
    //QObject::connect(ui->group_lbl, &OptionLabel::switchOptionSignal, stack_wnd, &StackedWidget::switchWidget);
    //QObject::connect(ui->setting_lbl, &OptionLabel::switchOptionSignal, stack_wnd, &StackedWidget::switchWidget);
}

void FriendWidget::initListWidget()
{
    //新的朋友栏
    QListWidget *list_wnd = ui->listWidget;
    QListWidgetItem *item = new QListWidgetItem(list_wnd);
    this->new_brief_wid = new NewFriendBriefWidget(this, list_wnd);
    item->setSizeHint(QSize(0, new_brief_wid->size().height()));
    list_wnd->setItemWidget(item, new_brief_wid);
}

void FriendWidget::initOtherWidgets()
{
    new_frnd_widget = new NewFriendWidget(this->stack_wnd);
    stack_wnd->addWidget(new_frnd_widget);
    frnd_detail_widget = new FriendDetailWidget(this->stack_wnd);
    stack_wnd->addWidget(frnd_detail_widget);

    new_frnd_widget->init();
    frnd_detail_widget->init();
}

void FriendWidget::goAheadToThisWidget()
{
    stack_wnd->switchWidget(wid_index);
}


void FriendWidget::newFriendRequireCome()
{
    new_brief_wid->flushNewFriendIcon(true);
}

void FriendWidget::allFriendsApplySlove()
{
    new_brief_wid->flushNewFriendIcon(false);
}

void FriendWidget::updateFriendsList(FrndInfoVectPtr frnd_infos)
{
    for (auto it = frnd_infos->begin(); it != frnd_infos->end(); ++it)
    {
        account_frndinfo_map.insert(it->account, *it);
    }
    QListWidget *list_wnd =  ui->listWidget;
    //先把所有的除newfriendbriefwidget外的移除，再获取新的
    for (int count = list_wnd->count() - 1; count > 0; --count)
    {
        delete list_wnd->takeItem(count);
    }
    QSize size(0, new_brief_wid->size().height());
    account_frndinfo_map_mutex.lock();
    for (auto& frnd_info: account_frndinfo_map)
    {
        QListWidgetItem *item = new QListWidgetItem(list_wnd);
        FriendBriefWidget *frnd_wid = new FriendBriefWidget(list_wnd);
        frnd_wid->setFriendInformation(frnd_info.account, frnd_info.nickname, frnd_info.label, frnd_info.username);
        item->setSizeHint(size);
        list_wnd->setItemWidget(item, frnd_wid);
    }
    account_frndinfo_map_mutex.unlock();
}

FriendBriefInfo FriendWidget::getFriendBriefInfo(const QString& account)
{
    QMutexLocker lock(&this->account_frndinfo_map_mutex);
    auto it = account_frndinfo_map.find(account);
    if (it == account_frndinfo_map.end())
    {
        return FriendBriefInfo();
    }
    return it.value();
}

bool FriendWidget::isMyFriend(const QString &account)
{
    QMutexLocker lock(&this->account_frndinfo_map_mutex);
    return account_frndinfo_map.contains(account);
}
