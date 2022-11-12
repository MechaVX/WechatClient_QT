#ifndef COMMUNICATIONMESSAGE_H
#define COMMUNICATIONMESSAGE_H

#include <QTime>

namespace communication_message
{

enum TargetType
{
    someone,
    group,
};

enum ContentType
{
    text,
    video,
    picture,
    file,
};

struct Message
{
    QTime time;
    //account
    QString sender;
    QString content;
    TargetType target_type;
    ContentType cont_type;
};

}



#endif // COMMUNICATIONMESSAGE_H
