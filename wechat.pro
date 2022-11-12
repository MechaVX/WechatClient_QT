QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basewidget.cpp \
    globaldefine.cpp \
    main.cpp \
    loginwidget.cpp \
    src/file/fileworker.cpp \
    src/tcp/basemessageworker.cpp \
    src/tcp/flushmessageworker.cpp \
    src/tcp/friendsmessageworker.cpp \
    src/tcp/settingmessageworker.cpp \
    src/tcp/tcphelper.cpp \
    src/tcp/tcpreceiveworker.cpp \
    src/tcp/tcpsendworker.cpp \
    src/tcp/tcpstandardmessage.cpp \
    src/uis/common/optionlabel.cpp \
    src/uis/common/stackedwidget.cpp \
    src/uis/opt_friend/friendbriefwidget.cpp \
    src/uis/opt_friend/friendwidget.cpp \
    src/uis/opt_friend/information/applyfrienddialog.cpp \
    src/uis/opt_friend/information/frienddetailwidget.cpp \
    src/uis/opt_friend/information/friendoperatorlabel.cpp \
    src/uis/opt_friend/new/newfriendoptionwidget.cpp \
    src/uis/opt_friend/new/newfriendwidget.cpp \
    src/uis/opt_friend/newfriendbriefwidget.cpp \
    src/uis/opt_group/groupwidget.cpp \
    src/uis/opt_message/friendmessagebriefwidget.cpp \
    src/uis/opt_message/listmessageitem.cpp \
    src/uis/opt_message/messagewidget.cpp \
    src/uis/opt_setting/settingwidget.cpp

HEADERS += \
    basewidget.h \
    globaldefine.h \
    inc/file/fileworker.h \
    inc/tcp/basemessageworker.h \
    inc/tcp/flushmessageworker.h \
    inc/tcp/friendsmessageworker.h \
    inc/tcp/settingmessageworker.h \
    inc/tcp/tcphelper.h \
    inc/tcp/tcpreceiveworker.h \
    inc/tcp/tcpsendworker.h \
    inc/tcp/tcpstandardmessage.h \
    inc/uis/common/friendbriefinfo.h \
    inc/uis/common/optionlabel.h \
    inc/uis/common/stackedwidget.h \
    inc/uis/opt_friend/friendbriefwidget.h \
    inc/uis/opt_friend/friendwidget.h \
    inc/uis/opt_friend/information/applyfrienddialog.h \
    inc/uis/opt_friend/information/frienddetailwidget.h \
    inc/uis/opt_friend/information/friendoperatorlabel.h \
    inc/uis/opt_friend/new/newfriendoptionwidget.h \
    inc/uis/opt_friend/new/newfriendwidget.h \
    inc/uis/opt_friend/newfriendbriefwidget.h \
    inc/uis/opt_group/groupwidget.h \
    inc/uis/opt_message/communicationmessage.h \
    inc/uis/opt_message/friendmessagebriefwidget.h \
    inc/uis/opt_message/listmessageitem.h \
    inc/uis/opt_message/messagewidget.h \
    inc/uis/opt_setting/settingwidget.h \
    loginwidget.h

FORMS += \
    loginwidget.ui \
    uifiles/common/stackedwidget.ui \
    uifiles/opt_friend/friendbriefwidget.ui \
    uifiles/opt_friend/friendwidget.ui \
    uifiles/opt_friend/information/applyfrienddialog.ui \
    uifiles/opt_friend/information/frienddetailwidget.ui \
    uifiles/opt_friend/new/newfriendoptionwidget.ui \
    uifiles/opt_friend/new/newfriendwidget.ui \
    uifiles/opt_friend/newfriendbriefwidget.ui \
    uifiles/opt_group/groupwidget.ui \
    uifiles/opt_message/friendmessagebriefwidget.ui \
    uifiles/opt_message/messagewidget.ui \
    uifiles/opt_setting/settingwidget.ui

INCLUDEPATH += \
    inc/tcp \
    inc/file \
    inc/uis/common \
    inc/uis/opt_message \
    inc/uis/opt_friend \
    inc/uis/opt_group \
    inc/uis/opt_setting \
    inc/uis/opt_friend/new \
    inc/uis/opt_friend/information



TRANSLATIONS += \
    wechat_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
