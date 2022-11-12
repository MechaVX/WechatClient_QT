#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class SettingWidget;
}

class StackedWidget;

class SettingWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(StackedWidget *parent = nullptr);
    ~SettingWidget();

    void init() override;
    void goAheadToThisWidget() override;
private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
