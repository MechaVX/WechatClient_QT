#include "groupwidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"
#include "ui_groupwidget.h"

GroupWidget::GroupWidget(StackedWidget *parent):
    BaseWidget(main_widgets_managing::group_widget, parent),
    ui(new Ui::GroupWidget)
{
    ui->setupUi(this);
}

GroupWidget::~GroupWidget()
{
    delete ui;
}

void GroupWidget::init()
{

}

void GroupWidget::goAheadToThisWidget()
{

}
