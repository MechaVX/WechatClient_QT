#ifndef FRIENDDETAILWIDGET_H
#define FRIENDDETAILWIDGET_H

#include <QWidget>
#include <QLabel>
#include "basewidget.h"
#include "friendbriefinfo.h"

namespace Ui {
class FriendDetailWidget;
}

class FriendDetailWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit FriendDetailWidget(QWidget *parent = nullptr);
    ~FriendDetailWidget();

    void init() override;
    void goAheadToThisWidget() override;
private:
    Ui::FriendDetailWidget *ui;

    FriendBriefInfo frnd_info;

public:
    void showUserInformation(const FriendBriefInfo& frnd_info);
public slots:
    void showUserInformation(const QString& account,
                               const QString& user_name,
                               const QString& nick_name,
                               const QString& label,
                               bool is_friend);
    void showUserNoFound(const QString& account_phone);

private slots:
    void executeOperationToUser(QLabel *lbl);
};

#endif // FRIENDDETAILWIDGET_H
