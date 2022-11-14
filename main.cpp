#include "loginwidget.h"
#include "tcpstandardmessage.h"
#include "friendbriefinfo.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    qRegisterMetaType<TCPMsgStruPtr>("TCPMsgStruPtr");
    qRegisterMetaType<FrndInfoVectPtr>("FrndInfoVectPtr");
    QApplication a(argc, argv);

    LoginWidget w;
    w.show();
    return a.exec();
}
