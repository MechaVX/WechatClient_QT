#ifndef APPLYFRIENDDIALOG_H
#define APPLYFRIENDDIALOG_H

#include <QDialog>

namespace Ui {
class ApplyFriendDialog;
}

class ApplyFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyFriendDialog(QWidget *parent = nullptr);
    ~ApplyFriendDialog();

    QString getLineText();
private:
    Ui::ApplyFriendDialog *ui;
};

#endif // APPLYFRIENDDIALOG_H
