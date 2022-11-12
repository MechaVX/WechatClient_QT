#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <string>
#include "basewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class LoginWidget;
}
QT_END_NAMESPACE


class TCPHelper;
class StackedWidget;

class LoginWidget : public BaseWidget
{
    Q_OBJECT

private:
    Ui::LoginWidget *ui;
    QPixmap *bk_img;
    QPixmap *lbl_img;
    TCPHelper *tcp_helper;
    //用于保存当前登录用户的账号
    std::string user_account;
    //登录成功后的界面
    StackedWidget *stack_wnd = nullptr;

    void setComponentsConnection();
    bool isAccountFormatCorrect(const QString& str);
    bool isPasswordFormatCorrect(const QString& str);
    bool isPhoneFormatCorrect(const QString& str);

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    void init() override;
    void goAheadToThisWidget() override;
    TCPHelper* getTCPHelper();
    std::string getAccount();
protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

signals:
public slots:
    void userRegisterSlot(bool success, QString msg);
    void userLoginSlot(bool success, QString msg);
public:

private:


};
#endif // LOGINWIDGET_H
