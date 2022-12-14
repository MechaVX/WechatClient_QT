#ifndef FLUSHMESSAGEWORKER_H
#define FLUSHMESSAGEWORKER_H

#include <QObject>
#include "basemessageworker.h"
#include "friendbriefinfo.h"

class FlushMessageWorker : public BaseMessageWorker
{
    Q_OBJECT
public:
    explicit FlushMessageWorker(QObject *parent = nullptr);

    void init();
    void startAll();
    void analizeMsgStru(QSharedPointer<TCPMessage> msg_stru) override;
signals:
    void updateFriends(FrndInfoVectPtr frnd_infos);

private:
    void flushFriend(QSharedPointer<TCPMessage> msg_stru);
};

#endif // FLUSHMESSAGEWORKER_H
