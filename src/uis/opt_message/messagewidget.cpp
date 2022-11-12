#include "messagewidget.h"
#include "ui_messagewidget.h"
#include "optionlabel.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "friendbriefinfo.h"
#include "listmessageitem.h"
#include "friendmessagebriefwidget.h"

#include <QPixmap>
#include <QListWidget>
#include <QtDebug>
#include <QIcon>

using namespace images_sources;

MessageWidget::MessageWidget(StackedWidget *parent) :
    BaseWidget(main_widgets_managing::message_widget, parent),
    ui(new Ui::MessageWidget),
    message_img(uis_opt_message_ena),
    friend_img(uis_opt_friend_dis),
    group_img(uis_opt_group_dis),
    setting_img(uis_opt_setting_dis),

    icon_file(uis_msg_icon_file),
    icon_video(uis_msg_icon_video),
    icon_image(uis_msg_icon_image),
    icon_send(uis_msg_icon_send),
    icon_clean(uis_msg_icon_clean),
    wid_index(0)
{
    ui->setupUi(this);

    stack_wnd = parent;

    QListWidget *list_wid = ui->listWidget;
    //使用降序排列，不要问为什么
    list_wid->sortItems(Qt::DescendingOrder);

    FriendBriefInfo frnd_info{ "1643616080", "label", "sss", "nick" };
    for (int i = 0; i < 15; ++i)
    {
        ListMessageItem *item = new ListMessageItem;
        item->init(list_wid, &frnd_info);
    }
    //搜索按钮
    ui->search_button->setIcon(QIcon(uis_search));
    ui->search_button->setStyleSheet("border: 0px");
    ui->search_button->setFlat(true);
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::init()
{
    initOptionLabels();
    initCommunicateQuickButtons();
}

void MessageWidget::goAheadToThisWidget()
{
    stack_wnd->switchWidget(wid_index);
}

void MessageWidget::initOptionLabels()
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

void MessageWidget::initCommunicateQuickButtons()
{
    ui->file_button->setIcon(icon_file);
    ui->file_button->setFlat(true);
    ui->file_button->setStyleSheet("border: 0px");
    ui->video_button->setIcon(icon_video);
    ui->video_button->setFlat(true);
    ui->video_button->setStyleSheet("border: 0px");
    ui->image_button->setIcon(icon_image);
    ui->image_button->setFlat(true);
    ui->image_button->setStyleSheet("border: 0px");
    ui->send_button->setIcon(icon_send);
    ui->send_button->setFlat(true);
    ui->send_button->setStyleSheet("border: 0px");
    ui->clean_button->setIcon(icon_clean);
    ui->clean_button->setFlat(true);
    ui->clean_button->setStyleSheet("border: 0px");
}



void MessageWidget::newMessageCome(communication_message::Message msg_stru, FriendBriefInfo *frnd_info)
{
    QListWidget *list_wnd = ui->listWidget;
    ListMessageItem *item;

    auto it = account_item_map.find(msg_stru.sender);
    if (msg_stru.target_type == communication_message::someone)
    {
        if (it == account_item_map.end())
        {
            item = new ListMessageItem;
            item->init(list_wnd, frnd_info);
            account_item_map.insert(msg_stru.sender, item);
        }
        else
        {
            item = it.value();
        }
        item->receiveNewMessage(msg_stru);
    }
    else
    {

    }

}

