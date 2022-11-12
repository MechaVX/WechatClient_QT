#ifndef FRIENDBRIEFWIDGET_H
#define FRIENDBRIEFWIDGET_H

#include <QWidget>

namespace Ui {
class FriendBriefWidget;
}

class FriendBriefWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FriendBriefWidget(QWidget *parent = nullptr);
    ~FriendBriefWidget();

    void setFriendInformation(const QString& account, const QString& nickname, const QString& label, const QString& username);
private:
    Ui::FriendBriefWidget *ui;

    QString account;
    QString nickname;
    QString label;
    QString username;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // FRIENDBRIEFWIDGET_H
