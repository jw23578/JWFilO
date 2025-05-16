#include "fileloadworker.h"
#include <QDir>

FileLoadWorker::FileLoadWorker(const QString &rootFilePath,
                               QObject *parent)
    : QObject{parent},
    rootFilePath(rootFilePath)
{}


void FileLoadWorker::loadAllFiles(const QDir &d)
{
    for (auto &e: d.entryInfoList())
    {
        if (e.isDir())
        {
            QString name(e.fileName());
            if (name != "." && name != "..")
            {
                QDir nd(e.absoluteFilePath());
                loadAllFiles(nd);
            }
        }
        if (e.isFile())
        {
            QFileInfo *fi(new QFileInfo(e));
            emit resultReady(fi);
        }
    }
}


void FileLoadWorker::doLoad()
{
    QDir d(rootFilePath);
    loadAllFiles(d);
    emit finished();
}
