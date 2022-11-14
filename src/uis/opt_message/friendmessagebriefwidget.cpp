#include "friendmessagebriefwidget.h"
#include "ui_friendmessagebriefwidget.h"
#include "globaldefine.h"

#include <QPixmap>
#include <QAction>
#include <QMenu>

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

bool FriendMessageBriefWidget::event(QEvent *ev)
{
    if (ev->type() != QEvent::MouseButtonPress)
        return true;
    return QWidget::event(ev);
}

void FriendMessageBriefWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction *act1 = new QAction("置顶", &menu);
        QAction *act2 = new QAction("删除", &menu);
        menu.addAction(act1);
        menu.addAction(act2);
        menu.exec(QCursor::pos());
    }
}
