#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "globaldefine.h"
#include "tcphelper.h"
#include "stackedwidget.h"

#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>


using namespace tcp_standard_message;

LoginWidget::LoginWidget(QWidget *parent)
    : BaseWidget(main_widgets_managing::login_widget, parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    init();
}


LoginWidget::~LoginWidget()
{
    this->prepareToExitProgess();
    delete ui;
    delete bk_img;
    delete lbl_img;

}

void LoginWidget::init()
{
    this->setWindowTitle("欢迎来到wechat");
    bk_img = new QPixmap(images_sources::login_background);
    lbl_img = new QPixmap(images_sources::login_label_img);

    //只能输入数字
    ui->account_edit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    //限定输入长度
    ui->account_edit->setMaxLength(11);
    ui->passwd_edit->setMaxLength(18);

    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->account_edit->setText("16436160790");
    ui->passwd_edit->setText("M4A1AK47");
    setComponentsConnection();

    tcp_helper = new TCPHelper;
    tcp_thread = new QThread;
    tcp_helper->moveToThread(tcp_thread);
    tcp_thread->start();
    //需要使用信号
    //tcp_helper->init();
    QObject::connect(this, &LoginWidget::initTCPHelperSignal, tcp_helper, &TCPHelper::init);
    emit initTCPHelperSignal();
    this->msg_helper = new TCPMessageHelper(this, tcp_helper);
}

void LoginWidget::goAheadToThisWidget()
{

}
/*
bool LoginWidget::isAccountFormatCorrect(const QString &str)
{
    if (str.length() != 10)
        return false;
    for (auto c: str)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

bool LoginWidget::isPasswordFormatCorrect(const QString &str)
{
    int len = str.length();
    if (len < 6 || len > 15)
        return false;
    for (QChar c: str)
    {
        if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
            return false;
    }
    return true;
}

bool LoginWidget::isPhoneFormatCorrect(const QString &str)
{
    if (str.length() != 11)
        return false;
    for (auto c: str)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}
*/
void LoginWidget::setComponentsConnection()
{
    QObject::connect(ui->login_button, &QPushButton::clicked, [this]()
    {
        QString qaccount = ui->account_edit->text();
        QString qpasswd = ui->passwd_edit->text();
        //防止用户多次按下
        ui->login_button->setDisabled(true);
        ui->register_button->setDisabled(true);
        QSharedPointer<TCPMessage> msg_stru = TCPMessage::createTCPMessage(setting, user_login, qaccount, TCPMessage::server_account ,{ qpasswd.toStdString() });
        if (!msg_helper->commitTCPMessage(msg_stru))
        {
            QMessageBox::critical(this, "连接错误", "无法连接至服务器，请检查网络后重试!");
            ui->login_button->setDisabled(false);
            ui->register_button->setDisabled(false);
        }
        /*
         * 测试粘包时用
        string tmp("abcdefghsssssssss23sfsfsfsfsofshfosfhsfoisssijklmnop");
        qDebug() << tmp.length();
        for (int i = 0; i < 15; ++i)
        {
            QSharedPointer<TCPMessage> msg_stru = TCPMessage::createTCPMessage(invalid, 1, { tmp, tmp, tmp, tmp }, qaccount);
            msg_helper->commitTCPMessage(msg_stru);
        }

        */
    });

    QObject::connect(ui->register_button, &QPushButton::clicked, [this]()
    {
        QString qphone = ui->account_edit->text();
        QString qpasswd = ui->passwd_edit->text();
        ui->login_button->setDisabled(true);
        ui->register_button->setDisabled(true);
        QSharedPointer<TCPMessage> msg_stru = TCPMessage::createTCPMessage(setting, user_register, qphone, TCPMessage::server_account, { qpasswd.toStdString() });
        if (!msg_helper->commitTCPMessage(msg_stru))
        {
            QMessageBox::critical(this, "连接错误", "无法连接至服务器，请检查网络后重试!");
            ui->login_button->setDisabled(false);
            ui->register_button->setDisabled(false);
        }
    });
}

void LoginWidget::userRegisterSlot(bool success, QString str)
{
    if (success)
    {
        QMessageBox::information(this, "提示", QString("注册成功，您的账号为%1。").arg(str));
    }
    else
    {
        QMessageBox::information(this, "错误", str);
    }
    ui->login_button->setDisabled(false);
    ui->register_button->setDisabled(false);
}

void LoginWidget::userLoginSlot(bool success, QString str)
{
    if (success)
    {
        this->user_account = ui->account_edit->text();

        stack_wnd = new StackedWidget;
        stack_wnd->init();

        QObject::connect(this, &LoginWidget::startAllTCPHelperSignal, tcp_helper, &TCPHelper::completelyStart,
                         (Qt::ConnectionType)(Qt::AutoConnection | Qt::UniqueConnection));
        emit startAllTCPHelperSignal();
        stack_wnd->startAll();
        stack_wnd->show();
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "错误", str);
        ui->login_button->setDisabled(false);
        ui->register_button->setDisabled(false);
    }
}

TCPHelper* LoginWidget::getTCPHelper()
{
    return this->tcp_helper;
}

QString LoginWidget::getAccount()
{
    return this->user_account;

}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), *bk_img);
}



void LoginWidget::closeEvent(QCloseEvent *event)
{
    auto ret = QMessageBox::information(this, "退出", "确定要退出Wechat?", QMessageBox::Yes, QMessageBox::No);
    if (ret != QMessageBox::Yes)
    {
        event->ignore();
        return;
    }
    event->accept();
}

void LoginWidget::prepareToExitProgess()
{
    QObject::connect(this, &LoginWidget::exitSignal, tcp_helper, &TCPHelper::prepareToExit);
    emit exitSignal();
    QThread::msleep(200);
    tcp_thread->quit();
    tcp_thread->exit();
    tcp_thread->deleteLater();
    tcp_helper->deleteLater();
}

