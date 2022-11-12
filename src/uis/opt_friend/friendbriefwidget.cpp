#include "friendbriefwidget.h"
#include "ui_friendbriefwidget.h"
#include "globaldefine.h"
#include "frienddetailwidget.h"

FriendBriefWidget::FriendBriefWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendBriefWidget)
{
    ui->setupUi(this);
}

FriendBriefWidget::~FriendBriefWidget()
{
    delete ui;
}

void FriendBriefWidget::setFriendInformation(const QString& account, const QString& nickname, const QString& label, const QString& username)
{
    this->account = account;
    this->nickname = nickname;
    this->label = label;
    this->username = username;
    ui->name_lbl->setText(nickname);
}

using namespace main_widgets_managing;

void FriendBriefWidget::mousePressEvent(QMouseEvent *event)
{
    FriendDetailWidget *frnd_det = dynamic_cast<FriendDetailWidget*>(getWidgetPointer(friend_detail_widget));
    frnd_det->showUserInformation(account, username, nickname, label, true);
}
