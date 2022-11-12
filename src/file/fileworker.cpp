#include "fileworker.h"


const char *FileWorker::base_path = "../wechat/cache/";

FileWorker::FileWorker(QObject *parent, const QString& account) : QObject(parent), account(account)
{

}


