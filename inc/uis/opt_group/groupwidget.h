#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class GroupWidget;
}

class StackedWidget;

class GroupWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit GroupWidget(StackedWidget *parent);
    ~GroupWidget();

    void init() override;
    void goAheadToThisWidget() override;
private:
    Ui::GroupWidget *ui;
};

#endif // GROUPWIDGET_H
