#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QObject>
#include <QFile>
#include <QFileDialog>

class FileWorker : public QObject
{
    Q_OBJECT
public:
    explicit FileWorker(QObject *parent, const QString& account);


signals:

private:
    static const char *base_path;

    QString account;
};

#endif // FILEWORKER_H
