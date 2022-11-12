#ifndef NEWFRIENDWIDGET_H
#define NEWFRIENDWIDGET_H

#include <QWidget>
#include <QMap>
#include "basewidget.h"

namespace Ui {
class NewFriendWidget;
}

class StackedWidget;
class QListWidgetItem;

class NewFriendWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit NewFriendWidget(StackedWidget *parent);
    ~NewFriendWidget();

    void init() override;
    void goAheadToThisWidget() override;

    void removeFriendApply(const QString& account);
private:
    Ui::NewFriendWidget *ui;

    StackedWidget *stack_wnd;

    //这是QListWidget中，根据账号找到NewFriendOptionWidget对应的item*
    QMap<QString, QListWidgetItem*> account_item_map;

private slots:
    void showFriendWidget();

    void searchUser();
    void notSuchUser(const QString& account);

public slots:
    void newFriendApplyCome(const QString& account, const QString& apply_msg);

};

#endif // NEWFRIENDWIDGET_H
