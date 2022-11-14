#ifndef STACKEDWIDGETUI1_H
#define STACKEDWIDGETUI1_H

#include <QStackedWidget>
#include <QCloseEvent>
#include <QStack>

namespace Ui {
class StackedWidget;
}


class BaseWidget;
class MessageWidget;
class FriendWidget;
class LoginWidget;
class TCPHelper;
class TCPMessageHelper;

class StackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = nullptr);
    ~StackedWidget();

    void init();
    void startAll();
    std::string getAccount();
private:
    Ui::StackedWidget *ui;
    LoginWidget *login_widget;

    //用于记录主窗口嵌套进入情况，其中栈顶为当前窗口指针
    QStack<BaseWidget*> wids_stack;

    MessageWidget *msg_wnd;
    FriendWidget *frd_wnd;
    TCPMessageHelper *msg_helper;

    std::string account;
    void userLogout(bool exit_progress = true);
    bool close_flag = false;
protected:
    void closeEvent(QCloseEvent *ev);

public:
    //如果是按返回按钮，wnd应传入nullptr，否则传入具体的窗口
    //初始的四大窗口中不调用该函数
    void switchWidget(BaseWidget *wnd);


public slots:
    //该函数仅由初始的四大窗口中调用
    void switchWidget(int index);
};

#endif // STACKEDWIDGETUI1_H
