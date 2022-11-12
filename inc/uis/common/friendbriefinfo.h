#ifndef FRIENDBRIEFINFO_H
#define FRIENDBRIEFINFO_H

#include <QString>

struct FriendBriefInfo
{
    QString account;
    QString label;
    QString nickname;
    QString username;
    inline operator bool() const
    {
        return account.isEmpty();
    }
    inline bool isValid() const
    {
        return account.isEmpty();
    }
};

#endif // FRIENDBRIEFINFO_H
