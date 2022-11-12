#include "inc/uis/opt_friend/new/newfriendoptionwidget.h"
#include "ui_newfriendoptionwidget.h"

NewFriendOptionWidget::NewFriendOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFriendOptionWidget)
{
    ui->setupUi(this);
}

NewFriendOptionWidget::~NewFriendOptionWidget()
{
    delete ui;
}
