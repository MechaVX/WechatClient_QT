#include "frienddetailwidget.h"
#include "friendwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "loginwidget.h"
#include "friendoperatorlabel.h"
#include "tcpstandardmessage.h"
#include "messagewidget.h"
#include "tcphelper.h"
#include "applyfrienddialog.h"
#include "ui_frienddetailwidget.h"

#include <QIcon>
#include <QMouseEvent>
#include <QMessageBox>

using namespace main_widgets_managing;
using namespace images_sources;

FriendDetailWidget::FriendDetailWidget(QWidget *parent) :
    BaseWidget(main_widgets_managing::friend_detail_widget, parent),
    ui(new Ui::FriendDetailWidget)
{
    ui->setupUi(this);
    ui->back_button->setIcon(QIcon(uis_goback));
    ui->back_button->setFlat(true);
    ui->back_button->setStyleSheet("border: 0px");
}

FriendDetailWidget::~FriendDetailWidget()
{
    delete ui;
}

void FriendDetailWidget::init()
{

    //FriendWidget *frnd_wnd = dynamic_cast<FriendWidget*>(getWidgetPointer(friend_widget));
    QObject::connect(ui->back_button, &QPushButton::clicked, [=]()
    {
        StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));
        stack_wnd->switchWidget(nullptr);
    });

    msg_helper = new TCPMessageHelper(this, dynamic_cast<LoginWidget*>(getWidgetPointer(login_widget))->getTCPHelper());

    QObject::connect(ui->modify_frnd_lbl, &FriendOperatorLabel::friendOperation, this, &FriendDetailWidget::executeOperationToUser);
    QObject::connect(ui->talk_lbl, &FriendOperatorLabel::friendOperation, this, &FriendDetailWidget::executeOperationToUser);
}

void FriendDetailWidget::showUserInformation(const FriendBriefInfo& frnd_info)
{
    showUserInformation(frnd_info.account, frnd_info.username, frnd_info.nickname, frnd_info.label, !frnd_info.label.isEmpty());
}

void FriendDetailWidget::showUserInformation(const QString& account,
                           const QString& user_name,
                           const QString& nick_name,
                           const QString& label,
                           bool is_friend)
{
    this->frnd_info = { account, label, nick_name, user_name };
    ui->account_lbl->setText(QString("账号 %1").arg(account));
    ui->nick_lbl->setText(QString("昵称 %1").arg(nick_name));
    ui->name_lbl->setText(QString("用户名 %1").arg(user_name));
    ui->lbl_lbl->setText(QString("标签 %1").arg(label));

    if (is_friend)
    {
        ui->modify_frnd_lbl->setText("删除该好友");
        ui->recommend_lbl->setText("推荐该好友");
        ui->recommend_lbl->setDisabled(false);
        ui->talk_lbl->setText("发送消息");
        ui->talk_lbl->setDisabled(false);
    }
    else
    {
        ui->modify_frnd_lbl->setText("添加该用户");
        ui->recommend_lbl->clear();
        ui->recommend_lbl->setDisabled(true);
        ui->talk_lbl->clear();
        ui->talk_lbl->setDisabled(true);
    }
    goAheadToThisWidget();

}

void FriendDetailWidget::showUserNoFound(const QString& account_phone)
{
    ui->account_lbl->setText(QString("未找到该用户: %1").arg(account_phone));
    ui->nick_lbl->clear();
    ui->name_lbl->clear();
    ui->lbl_lbl->clear();
    ui->recommend_lbl->clear();
    ui->modify_frnd_lbl->clear();
    ui->recommend_lbl->setDisabled(true);
    ui->talk_lbl->clear();
    ui->talk_lbl->setDisabled(true);
    goAheadToThisWidget();
}


void FriendDetailWidget::goAheadToThisWidget()
{
    StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));
    stack_wnd->switchWidget(this);
}

using namespace tcp_standard_message;
void FriendDetailWidget::executeOperationToUser(QLabel *lbl)
{
    StackedWidget *stack_wnd = dynamic_cast<StackedWidget*>(getWidgetPointer(stack_widget));
    QString str = lbl->text();

    QString tmp = ui->account_lbl->text();
    //移除"账户 "字符，剩下账号
    QString frnd_account = tmp.remove(0, tmp.indexOf(' ') + 1);

    if (str == "添加该用户")
    {
        ApplyFriendDialog apply_dialog;
        apply_dialog.exec();
        int ret = apply_dialog.result();
        if (ret != 1)
            return;


        std::vector<std::string> apply_msg{ apply_dialog.getLineText().toStdString() };
        auto msg_stru = TCPMessage::createTCPMessage(friends, add_friend, stack_wnd->getAccount(), frnd_account, apply_msg);
        if (msg_helper->commitTCPMessage(msg_stru))
        {
            QMessageBox::information(this, "申请成", "已提交申请，请待对方认证！");
        }
    }

    else if (str == "发送消息")
    {
        qDebug() << "send message to user";
        MessageWidget *msg_wid = dynamic_cast<MessageWidget*>(getWidgetPointer(message_widget));
        communication_message::Message msg_stru;
        msg_stru.time = QTime::currentTime();
        qDebug() << msg_stru.time;
        msg_stru.sender = frnd_account;
        msg_stru.target_type = communication_message::someone;
        msg_stru.cont_type = communication_message::text;
        msg_wid->newMessageCome(std::move(msg_stru), &frnd_info);
        msg_wid->goAheadToThisWidget();
    }
}
