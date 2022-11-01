#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE


class TCPHelper;

class LoginWidget : public QWidget
{
    Q_OBJECT


private:
    Ui::LoginWidget *ui;
    QPixmap *bk_img;
    QPixmap *lbl_img;
    TCPHelper *tcp_helper;


    void setComponentsConnection();
    bool isAccountFormatCorrect(const QString& str);
    bool isPasswordFormatCorrect(const QString& str);
    bool isPhoneFormatCorrect(const QString& str);

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

protected:
    void paintEvent(QPaintEvent *event);
    //void closeEvent(QCloseEvent *event) override;

private:

signals:
public slots:
    void userRegisterSlot(bool success, QString msg);
    void userLoginSlot(bool success, QString msg);


};
#endif // LOGINWIDGET_H
