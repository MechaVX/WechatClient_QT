#ifndef NEWFRIENDBRIEFWIDGET_H
#define NEWFRIENDBRIEFWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>

namespace Ui {
class NewFriendBriefWidget;
}

class FriendWidget;

class NewFriendBriefWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewFriendBriefWidget(FriendWidget *frnd_wnd, QWidget *parent);
    ~NewFriendBriefWidget();

    //更新显示图标
    void newFriendApplyCome();
private:
    Ui::NewFriendBriefWidget *ui;

    QPixmap new_frnd_img;
    QPixmap no_new_frnd_img;

    FriendWidget *frnd_wnd;
    void initLabelImage();
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // NEWFRIENDBRIEFWIDGET_H
