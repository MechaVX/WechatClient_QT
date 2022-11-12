#include "settingwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(StackedWidget *parent) :
    BaseWidget(main_widgets_managing::setting_widget, parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::init()
{

}

void SettingWidget::goAheadToThisWidget()
{

}
