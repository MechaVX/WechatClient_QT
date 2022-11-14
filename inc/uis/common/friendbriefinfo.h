#ifndef FRIENDBRIEFINFO_H
#define FRIENDBRIEFINFO_H

#include <QString>
#include <QVector>
#include <QSharedPointer>

struct FriendBriefInfo
{
    QString account;
    QString label;
    QString nickname;
    QString username;
    inline operator bool() const
    {
        return account.length() != 0;
    }
    inline bool isValid() const
    {
        return account.length() != 0;
    }
};

typedef QSharedPointer<QVector<FriendBriefInfo> > FrndInfoVectPtr;

#endif // FRIENDBRIEFINFO_H
