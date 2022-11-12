#include "newfriendwidget.h"
#include "ui_newfriendwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "friendwidget.h"
#include "frienddetailwidget.h"
#include "newfriendoptionwidget.h"
#include "tcphelper.h"

#include <QIcon>
#include <QPushButton>
#include "QMessageBox"

using namespace images_sources;
using namespace main_widgets_managing;

NewFriendWidget::NewFriendWidget(StackedWidget *parent) :
    BaseWidget(main_widgets_managing::new_friend_widget, parent),
    ui(new Ui::NewFriendWidget),
    stack_wnd(parent)
{
    ui->setupUi(this);
}

NewFriendWidget::~NewFriendWidget()
{
    delete ui;
}

void NewFriendWidget::init()
{

    ui->search_button->setIcon(QIcon(uis_search));
    ui->search_button->setFlat(true);
    ui->search_button->setStyleSheet("border: 0px");
    ui->back_button->setIcon(QIcon(uis_goback));
    ui->back_button->setFlat(true);
    ui->back_button->setStyleSheet("border: 0px");
    //只能输入数字
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    //限定输入长度
    ui->lineEdit->setMaxLength(11);

    QObject::connect(ui->search_button, &QPushButton::clicked, this, &NewFriendWidget::searchUser);

    QObject::connect(ui->back_button, &QPushButton::clicked, [=]()
    {
        stack_wnd->switchWidget(nullptr);
    });

}

void NewFriendWidget::showFriendWidget()
{
    FriendWidget *frnd_wnd = dynamic_cast<FriendWidget*>(getWidgetPointer(friend_widget));
    stack_wnd->setCurrentWidget(frnd_wnd);
}

void NewFriendWidget::goAheadToThisWidget()
{
    stack_wnd->switchWidget(this);
}

using namespace tcp_standard_message;
void NewFriendWidget::searchUser()
{
    QString str = ui->lineEdit->text();
    if (str.length() < 10)
        return;
    if (stack_wnd->getAccount() == str.toStdString())
    {
        qDebug() << "转到自己的账号信息里";
        return;
    }
    FriendWidget *frnd_wnd = dynamic_cast<FriendWidget*>(getWidgetPointer(friend_widget));
    FriendBriefInfo frnd_info = frnd_wnd->getFriendBriefInfo(str);
    if (frnd_info)
    {
        FriendDetailWidget *frnd_det_wnd = dynamic_cast<FriendDetailWidget*>(getWidgetPointer(friend_detail_widget));
        frnd_det_wnd->showUserInformation(frnd_info);
        return;
    }
    TCPHelper *tcp_helper = stack_wnd->getTCPHelper();
    auto msg_stru = TCPMessage::createTCPMessage(friends, search_someone, {str.toStdString()});
    qDebug() << msg_stru->data_buf;
    tcp_helper->commitTCPMessage(msg_stru);
}

void NewFriendWidget::notSuchUser(const QString& account)
{
    QMessageBox::information(this, "未知用户", QString("未找到该用户:%1!").arg(account), QMessageBox::Ok);
}

void NewFriendWidget::newFriendApplyCome(const QString& account, const QString& apply_msg)
{
    QListWidget *list_wnd = ui->listWidget;
    QListWidgetItem *item = new QListWidgetItem(list_wnd);
    NewFriendOptionWidget *opt_wnd = new NewFriendOptionWidget(this);
    opt_wnd->init(account, account, apply_msg);
    item->setSizeHint(QSize(0, opt_wnd->size().height()));
    list_wnd->setItemWidget(item, opt_wnd);
    account_item_map.insert(account, item);
}


void NewFriendWidget::removeFriendApply(const QString& account)
{
    QListWidgetItem *item = account_item_map[account];
    ui->listWidget->removeItemWidget(item);
    delete item;
}
