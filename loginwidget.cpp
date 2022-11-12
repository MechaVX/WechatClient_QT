#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "globaldefine.h"
#include "inc/tcp/tcphelper.h"
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
    delete ui;
    delete bk_img;
    delete lbl_img;

}

void LoginWidget::init()
{
    this->setWindowTitle("欢迎来到wechat");
    bk_img = new QPixmap(images_sources::login_background);
    lbl_img = new QPixmap(images_sources::login_label_img);
    //ui->img_lbl->setPixmap(*lbl_img);
    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->account_edit->setText("1643616079");
    ui->passwd_edit->setText("M4A1AK47");
    tcp_helper = new TCPHelper(this);
    setComponentsConnection();
}

void LoginWidget::goAheadToThisWidget()
{

}

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

void LoginWidget::setComponentsConnection()
{
    QObject::connect(ui->login_button, &QPushButton::clicked, [this]()
    {
        QString qaccount = ui->account_edit->text();
        if (!isAccountFormatCorrect(qaccount))
        {
            QMessageBox::information(this, "提示", "账号格式不正确，应为10位数字！");
            return;
        }
        QString qpasswd = ui->passwd_edit->text();
        if (!isPasswordFormatCorrect(qpasswd))
        {
            QMessageBox::information(this, "提示", "密码格式不正确，长度应为6~15位数字和字母组合！");
            return;
        }
        //防止用户多次按下
        ui->login_button->setDisabled(true);
        ui->register_button->setDisabled(true);
        qDebug() << "LoginWidget::setComponentsConnection";
        QSharedPointer<TCPMessage> msg_stru = TCPMessage::createTCPMessage(setting, user_login, { qaccount.toStdString(), qpasswd.toStdString() });
        if (!tcp_helper->commitTCPMessage(msg_stru))
        {
            QMessageBox::critical(this, "连接错误", "无法连接至服务器，请检查网络后重试!");
            ui->login_button->setDisabled(false);
            ui->register_button->setDisabled(false);
        }
    });

    QObject::connect(ui->register_button, &QPushButton::clicked, [this]()
    {
        QString qphone = ui->account_edit->text();
        if (!isPhoneFormatCorrect(qphone))
        {
            QMessageBox::information(this, "提示", "手机号码格式不正确，应为11位数字！");
            return;
        }
        QString qpasswd = ui->passwd_edit->text();
        if (!isPasswordFormatCorrect(qpasswd))
        {
            QMessageBox::information(this, "提示", "密码格式不正确，长度应为6~15位数字和字母组合！");
            return;
        }
        ui->login_button->setDisabled(true);
        ui->register_button->setDisabled(true);
        QSharedPointer<TCPMessage> msg_stru = TCPMessage::createTCPMessage(setting, user_register, { qphone.toStdString(), qpasswd.toStdString() });
        qDebug() << "LoginWidget::setComponentsConnection";
        if (!tcp_helper->commitTCPMessage(msg_stru))
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
        this->user_account = ui->account_edit->text().toStdString();

        //注意这里不是setparent
        stack_wnd = new StackedWidget;
        stack_wnd->init();
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

std::string LoginWidget::getAccount()
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


