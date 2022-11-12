#include "newfriendoptionwidget.h"
#include "ui_newfriendoptionwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "newfriendwidget.h"
#include "tcpstandardmessage.h"
#include "tcphelper.h"

#include <QDebug>

using namespace images_sources;
using namespace main_widgets_managing;
using namespace tcp_standard_message;

NewFriendOptionWidget::NewFriendOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFriendOptionWidget),
    frnd_img(test_img)
{
    ui->setupUi(this);

}

NewFriendOptionWidget::~NewFriendOptionWidget()
{
    delete ui;
}


void NewFriendOptionWidget::init(const QString &account, const QString &user_name, const QString &message)
{
    this->account = account;
    this->nickname = user_name;
    this->message = message;
    ui->image_lbl->setPixmap(frnd_img);
    ui->message_lbl->setText(message);

    QObject::connect(ui->accept_button, &QPushButton::clicked, [=]()
    {
        StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));
        TCPHelper *tcp_helper = stack_wnd->getTCPHelper();

        auto msg_stru = TCPMessage::createTCPMessage(friends, agree_add_friend, { stack_wnd->getAccount(), account.toStdString()});
        tcp_helper->commitTCPMessage(msg_stru);
        //重新刷新好友列表
        msg_stru = TCPMessage::createTCPMessage(tcp_standard_message::flush, flush_friends, { stack_wnd->getAccount() } );
        tcp_helper->commitTCPMessage(msg_stru);

        //
        NewFriendWidget *frnd_wnd = dynamic_cast<NewFriendWidget*>(getWidgetPointer(new_friend_widget));
        frnd_wnd->removeFriendApply(account);
    });

    QObject::connect(ui->refuse_button, &QPushButton::clicked, [=]()
    {
        NewFriendWidget *frnd_wnd = dynamic_cast<NewFriendWidget*>(getWidgetPointer(new_friend_widget));
        frnd_wnd->removeFriendApply(account);
    });
}
