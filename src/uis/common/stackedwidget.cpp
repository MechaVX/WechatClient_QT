#include "inc/tcp/tcpstandardmessage.h"
#include "inc/tcp/tcphelper.h"
#include "stackedwidget.h"
#include "friendwidget.h"
#include "messagewidget.h"
#include "loginwidget.h"
#include "globaldefine.h"
#include "ui_stackedwidget.h"

#include <QMessageBox>
#include <QTimer>



StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWidget)
{
    ui->setupUi(this);
    //注册窗口名字
    main_widgets_managing::registerWidget(main_widgets_managing::stack_widget, this);

    login_widget = dynamic_cast<LoginWidget*>(main_widgets_managing::getWidgetPointer(main_widgets_managing::login_widget));
    this->account = login_widget->getAccount();
    this->setWindowTitle(QString("Wechat") + account.data());

    this->setAttribute(Qt::WA_DeleteOnClose);


}

StackedWidget::~StackedWidget()
{
    delete ui;
    //注销窗口名字
    main_widgets_managing::unsetWidget(main_widgets_managing::stack_widget);
}

using namespace tcp_standard_message;
void StackedWidget::init()
{
    msg_wnd = new MessageWidget(this);
    frd_wnd = new FriendWidget(this);
    //务必先add后init
    this->addWidget(msg_wnd);
    this->addWidget(frd_wnd);
    msg_wnd->init();
    frd_wnd->init();

    this->wids_stack.push(msg_wnd);

}

void StackedWidget::startAll()
{
    this->msg_helper = new TCPMessageHelper(this, login_widget->getTCPHelper());
    //获取新消息
    auto msg_stru = TCPMessage::createTCPMessage(tcp_standard_message::flush, flush_message, { account });
    msg_helper->commitTCPMessage(msg_stru);
    //获取朋友列表
    msg_stru = TCPMessage::createTCPMessage(tcp_standard_message::flush, flush_friends, { account });
    msg_helper->commitTCPMessage(msg_stru);

}


using namespace tcp_standard_message;
void StackedWidget::closeEvent(QCloseEvent *ev)
{
    if (close_flag)
    {
        ev->accept();
        return;
    }
    auto ret = QMessageBox::information(this, "退出Wechat", "确定要退出Wechat吗？", QMessageBox::Yes, QMessageBox::No);
    if (ret != QMessageBox::Yes)
    {
        ev->ignore();
        return;
    }
    this->userLogout();
    ev->ignore();
}

void StackedWidget::userLogout(bool exit_progress)
{
    QTimer *timer = new QTimer(this);
    timer->start(500);
    auto msg_stru = TCPMessage::createTCPMessage(setting, user_logout, { account });
    msg_helper->commitTCPMessage(msg_stru);
    QObject::connect(timer, &QTimer::timeout, [=]()
    {
        timer->stop();
        //注意这里加this
        this->close_flag = true;
        this->close();
        if (!exit_progress)
            login_widget->show();
    });
}

void StackedWidget::switchWidget(int index)
{
    if (index == this->currentIndex())
        return;
    this->wids_stack.pop();
    this->wids_stack.push(dynamic_cast<BaseWidget*>(this->widget(index)));
    this->setCurrentIndex(index);
}

void StackedWidget::switchWidget(BaseWidget *wnd)
{
    if (wnd == nullptr)
        this->wids_stack.pop();
    else
        this->wids_stack.push(wnd);
    this->setCurrentWidget(wids_stack.top());
}


std::string StackedWidget::getAccount()
{
    return account;
}
