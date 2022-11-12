#include "letterindexwidget.h"
#include "ui_LetterIndexWidget.h"

LetterIndexWidget::LetterIndexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LetterIndexWidget)
{
    ui->setupUi(this);
}

LetterIndexWidget::~LetterIndexWidget()
{
    delete ui;
}
