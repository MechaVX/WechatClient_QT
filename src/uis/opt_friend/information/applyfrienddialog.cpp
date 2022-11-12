#include "applyfrienddialog.h"
#include "ui_applyfrienddialog.h"

#include <QLineEdit>

ApplyFriendDialog::ApplyFriendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplyFriendDialog)
{
    ui->setupUi(this);

}

ApplyFriendDialog::~ApplyFriendDialog()
{
    delete ui;
}

QString ApplyFriendDialog::getLineText()
{
    return ui->lineEdit->text();
}
