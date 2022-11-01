#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QString>



QT_BEGIN_NAMESPACE



namespace images_sources
{

extern const QString base_path;

//login
extern const QString login_path ;
extern const QString login_background;
extern const QString login_label_img;

}

namespace server_config
{

extern const QString server_ip;
extern const quint16 server_port;

}




QT_END_NAMESPACE

#endif // GLOBALDEFINE_H
