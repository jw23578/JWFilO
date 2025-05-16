#ifndef FILELOADWORKER_H
#define FILELOADWORKER_H

#include <QObject>
#include <QFileInfo>

class FileLoadWorker : public QObject
{
    Q_OBJECT
    QString rootFilePath;
public:
    explicit FileLoadWorker(const QString &rootFilePath, QObject *parent = nullptr);

public slots:
    void doLoad();

signals:
    void resultReady(QFileInfo *fi);
    void finished();
private:
    void loadAllFiles(const QDir &d);
};

#endif // FILELOADWORKER_H
