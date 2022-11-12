#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QString>
#include <QWidget>


QT_BEGIN_NAMESPACE



namespace images_sources
{

extern const QString base_path;

extern const QString test_img;

//login
extern const QString login_path ;
extern const QString login_background;
extern const QString login_label_img;

//uis
extern const QString uis_path;
extern const QString uis_opt_message_dis;
extern const QString uis_opt_friend_dis;
extern const QString uis_opt_group_dis;
extern const QString uis_opt_setting_dis;
extern const QString uis_opt_message_ena;
extern const QString uis_opt_friend_ena;
extern const QString uis_opt_group_ena;
extern const QString uis_opt_setting_ena;

extern const QString uis_search;
extern const QString uis_add;
extern const QString uis_goback;

//opt_message
extern const QString uis_msg_icon_path;
extern const QString uis_msg_icon_file;
extern const QString uis_msg_icon_video;
extern const QString uis_msg_icon_image;
extern const QString uis_msg_icon_send;
extern const QString uis_msg_icon_clean;

//opt_friend
extern const QString uis_frnd_icon_path;
extern const QString uis_frnd_icon_new;
extern const QString uis_frnd_icon_no_new;

}

namespace server_config
{

extern const QString server_ip;
extern const quint16 server_port;

}


//为了方便使用窗口时找到对象，所有的主窗口生成后都要在此注册
//所有主窗口的析构函数中都将
namespace main_widgets_managing
{

extern const QString login_widget;

extern const QString stack_widget;

extern const QString message_widget;

extern const QString friend_widget;
extern const QString friend_detail_widget;
extern const QString new_friend_widget;

extern const QString group_widget;
extern const QString setting_widget;



//widget_name只能是以上所列
void registerWidget(const QString& widget_name, QWidget *widget);
QWidget* getWidgetPointer(const QString& widget_name);
void unsetWidget(const QString& widget_name);

}


//替代原有动态转化，当转化失败时能够提示
template<typename Tsrc, typename Tdest>
Tdest DynamicCast(Tsrc scr, Tdest dest);

QT_END_NAMESPACE

/*
 * qDebug() << "\033[*m" << ...
 * 其中*可显示不同格式，取值如下
0 : Reset Color Attributes
　　1 : 加粗
　　2 : 去粗
　　4 : 下划线
　　5 : 闪烁
　　7 : 反色
　　21/22 : 加粗 正常
　　24 : 去掉下划线
　　25 : 停止闪烁
　　27 : 反色
　　30 : 前景，黑色
　　31 : 前景，红色
　　32 : 前景，绿色
　　33 : 前景，黄色
　　34 : 前景，篮色
　　35 : 前景，紫色
　　36 : 前景，青色
　　37 : 前景，白色
　　40 : 背景，黑色
　　41 : 背景，红色
　　42 : 背景，绿色
　　43 : 背景，黄色
　　44 : 背景，篮色
　　45 : 背景，紫色
　　46 : 背景，青色
　　47 : 背景，白色
*/


#endif // GLOBALDEFINE_H
