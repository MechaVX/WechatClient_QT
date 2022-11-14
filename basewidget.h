#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class StackedWidget;
class TCPMessageHelper;

//为了在globaldefine上注册名字，所有主窗口（除了stackedwidget）都应该继承该类
class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(const QString& widget_name, QWidget *parent = nullptr);
    ~BaseWidget();

    virtual void goAheadToThisWidget() = 0;
    virtual void init() = 0;


private:
    const QString widget_name;

protected:
    TCPMessageHelper *msg_helper;
};

#endif // BASEWIDGET_H
