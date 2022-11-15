#include "newfriendbriefwidget.h"
#include "ui_newfriendbriefwidget.h"
#include "globaldefine.h"
#include "newfriendwidget.h"
#include "friendwidget.h"

#include <QPixmap>
#include <QDebug>

using namespace images_sources;
using namespace main_widgets_managing;

NewFriendBriefWidget::NewFriendBriefWidget(FriendWidget *frnd_wnd, QWidget *parent):
    QWidget(parent),
    ui(new Ui::NewFriendBriefWidget),
    new_frnd_img(uis_frnd_icon_new),
    no_new_frnd_img(uis_frnd_icon_no_new)
{
    ui->setupUi(this);
    this->frnd_wnd = frnd_wnd;
    initLabelImage();

}

NewFriendBriefWidget::~NewFriendBriefWidget()
{
    delete ui;
}

void NewFriendBriefWidget::initLabelImage()
{
    ui->img_lbl->setPixmap(no_new_frnd_img);
}

void NewFriendBriefWidget::mousePressEvent(QMouseEvent *event)
{
    NewFriendWidget *new_frnd_wnd = dynamic_cast<NewFriendWidget*>(getWidgetPointer(new_friend_widget));
    new_frnd_wnd->goAheadToThisWidget();
}

void NewFriendBriefWidget::flushNewFriendIcon(bool has_new_friend)
{
    if (has_new_friend)
        ui->img_lbl->setPixmap(new_frnd_img);
    else
        ui->img_lbl->setPixmap(no_new_frnd_img);
}
