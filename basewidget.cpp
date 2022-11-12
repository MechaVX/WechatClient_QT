#include "basewidget.h"
#include "globaldefine.h"
#include "stackedwidget.h"

using namespace main_widgets_managing;

BaseWidget::BaseWidget(const QString& widget_name, QWidget *parent):
    QWidget(parent),
    widget_name(widget_name)
{
    registerWidget(widget_name, this);
}

BaseWidget::~BaseWidget()
{
    unsetWidget(widget_name);
}

