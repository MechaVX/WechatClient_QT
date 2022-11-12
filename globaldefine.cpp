#include "globaldefine.h"

QT_BEGIN_NAMESPACE

#include <QDebug>
#include <QSet>
#include <QMap>
#include <QReadWriteLock>

namespace images_sources
{

const QString base_path = "../wechat/Images/";

const QString test_img = base_path + "test.jpg";

//login
const QString login_path = base_path + "login/";
const QString login_background = login_path + "background.jpg";
const QString login_label_img = login_path + "label_bk.jpg";


//uis
const QString uis_path = base_path + "uis/";
const QString uis_opt_message_dis = uis_path + "message_disable.png";
const QString uis_opt_friend_dis = uis_path + "friend_disable.png";
const QString uis_opt_group_dis = uis_path + "group_disable.png";
const QString uis_opt_setting_dis = uis_path + "setting_disable.png";
const QString uis_opt_message_ena = uis_path + "message_enable.png";
const QString uis_opt_friend_ena = uis_path + "friend_enable.png";
const QString uis_opt_group_ena = uis_path + "group_enable.png";
const QString uis_opt_setting_ena = uis_path + "setting_disable.png";
const QString uis_search = uis_path + "search.png";
const QString uis_add = uis_path + "add.png";
const QString uis_goback = uis_path + "goback.png";

//opt_message
const QString uis_msg_icon_path = uis_path + "message_widget/";
const QString uis_msg_icon_file = uis_msg_icon_path + "file.png";
const QString uis_msg_icon_video = uis_msg_icon_path + "video.png";
const QString uis_msg_icon_image = uis_msg_icon_path + "image.png";
const QString uis_msg_icon_send = uis_msg_icon_path + "send.png";
const QString uis_msg_icon_clean = uis_msg_icon_path + "clean.png";

//opt_friend
const QString uis_frnd_icon_path = uis_path + "friend_widget/";
const QString uis_frnd_icon_new = uis_frnd_icon_path + "new_friend.png";
const QString uis_frnd_icon_no_new = uis_frnd_icon_path + "no_new_friend.png";

}

namespace server_config
{

const QString server_ip = "192.168.1.103";
const quint16 server_port = 7777;

}


//为了方便使用窗口时找到对象，所有的主窗口生成后都要在此注册
//所有主窗口的析构函数中都将
namespace main_widgets_managing
{

const QString login_widget = "login";

const QString stack_widget = "stack";

const QString message_widget = "message";

const QString friend_widget = "friend";
const QString friend_detail_widget = "friend_detail";
const QString new_friend_widget = "new_friend";

const QString group_widget = "group";
const QString setting_widget = "setting";

//用于判断一个widget_name是否合法
static QSet<QString> widgets_set{
    login_widget, stack_widget, message_widget, friend_widget, friend_detail_widget, new_friend_widget,
    group_widget, setting_widget,
};
static QReadWriteLock widgets_lock;
static QMap<QString, QWidget*> widgets_map;

void registerWidget(const QString& widget_name, QWidget *widget)
{
    if (!widgets_set.contains(widget_name))
    {
        qDebug() << "in file globaldefine.cpp" << " registerWidget unknown widget_name:" << widget_name;
        return;
    }
    widgets_lock.lockForWrite();
    widgets_map[widget_name] = widget;
    widgets_lock.unlock();
}

QWidget* getWidgetPointer(const QString& widget_name)
{
    QWidget *result = nullptr;
    widgets_lock.lockForRead();
    auto it = widgets_map.find(widget_name);
    if (it == widgets_map.end())
    {
        qDebug() << "in file globaldefine.cpp" << " getWidgetPointer can not find key:" << widget_name;
    }
    else
    {
        result = it.value();
    }
    widgets_lock.unlock();
    return result;
}

void unsetWidget(const QString& widget_name)
{
    widgets_lock.lockForWrite();
    auto it = widgets_map.find(widget_name);
    if (it == widgets_map.end())
    {
        qDebug() << "in file globaldefine.cpp" << " unsetWidget can not find key:" << widget_name;
    }
    else
    {
        widgets_map.erase(it);
    }
    widgets_lock.unlock();
}

}


template<typename Tsrc, typename Tdest>
Tdest DynamicCast(Tsrc src)
{
    Tdest result = dynamic_cast<Tdest*>(src);
    if (result == nullptr)
    {
        qDebug() << "dynamic_cast error:" << src;
    }
    return result;
}

QT_END_NAMESPACE
