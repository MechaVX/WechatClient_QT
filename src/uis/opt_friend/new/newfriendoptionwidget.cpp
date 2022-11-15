#include "newfriendoptionwidget.h"
#include "ui_newfriendoptionwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "newfriendwidget.h"
#include "tcpstandardmessage.h"
#include "loginwidget.h"
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


void NewFriendOptionWidget::init(const QString &frnd_account, const QString &user_name, const QString &message)
{

    msg_helper = new TCPMessageHelper(this, dynamic_cast<LoginWidget*>(getWidgetPointer(login_widget))->getTCPHelper());

    this->account = frnd_account;
    this->nickname = user_name;
    this->message = message;
    ui->image_lbl->setPixmap(frnd_img);
    ui->message_lbl->setText(message);

    auto remove_apply = [&]()
    {
        //将该项申请移除
        NewFriendWidget *new_frnd_wnd = dynamic_cast<NewFriendWidget*>(getWidgetPointer(new_friend_widget));
        new_frnd_wnd->removeFriendApply(account);
        //给friendwidget更新图标（如果好友申请已经完全处理完毕）

    };

    QObject::connect(ui->accept_button, &QPushButton::clicked, [=]()
    {
        StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));

        auto msg_stru = TCPMessage::createTCPMessage(friends, agree_add_friend, stack_wnd->getAccount(), frnd_account);
        msg_helper->commitTCPMessage(msg_stru);
        //重新刷新好友列表
        msg_stru = TCPMessage::createTCPMessage(tcp_standard_message::flush, flush_friends, stack_wnd->getAccount());
        msg_helper->commitTCPMessage(msg_stru);

        remove_apply();
    });

    QObject::connect(ui->refuse_button, &QPushButton::clicked, remove_apply);
}

void NewFriendOptionWidget::flushApplyMessage(const QString& message)
{
    this->message = message;
    ui->message_lbl->setText(message);
}
