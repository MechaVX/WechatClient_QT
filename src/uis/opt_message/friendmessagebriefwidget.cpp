#include "friendmessagebriefwidget.h"
#include "ui_friendmessagebriefwidget.h"
#include "globaldefine.h"

#include <QPixmap>

using namespace images_sources;

FriendMessageBriefWidget::FriendMessageBriefWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendMessageBriefWidget)
{
    ui->setupUi(this);
    ui->img_lbl->setPixmap(QPixmap(test_img));

}

FriendMessageBriefWidget::~FriendMessageBriefWidget()
{
    delete ui;
}

void FriendMessageBriefWidget::init(const FriendBriefInfo &frnd_info)
{
    this->frnd_info = frnd_info;
    ui->sender_lbl->setText(frnd_info.nickname);
}

void FriendMessageBriefWidget::flushMessageDisplay(const communication_message::Message& msg_stru)
{
    this->ui->content_lbl->setText(msg_stru.content);
}
