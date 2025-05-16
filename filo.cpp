#include "filo.h"
#include "fileloadworker.h"
#include <QImage>
#include <QGuiApplication>
#include <QClipboard>
#include <QPixmap>
#include <QMimeData>
#include <QBuffer>

QString FilO::suffix2type(const QString &suffix) const
{
    auto it(knownSufix2Types.find(suffix.toLower()));
    if (it == knownSufix2Types.end())
    {
        return knownSufix2Types["unknown"];
    }
    return it.value();
}

void FilO::loadAllFiles(const QDir &d)
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
            allFiles.append(new QFileInfo(e));
            QString suffix(e.suffix().toLower());
            QString type(suffix2type(suffix));
            TypeObject *to(typeModel()->getById(type));
            if (!to)
            {
                to = new TypeObject;
                to->setId(type);
                typeModel()->append(to);
            }
            to->addFileInfo(suffix, allFiles.last());
        }
    }
}

void FilO::findDuplicates(const QString &suffix)
{
    QMap<qint64, QVector<QFileInfo*>> &size2FileInfos(suffix2Size2FileInfos[suffix]);
    auto it(size2FileInfos.begin());
    while (it != size2FileInfos.end())
    {
        QVector<QFileInfo*> &vec(it.value());
        if (vec.size() > 1)
        {
            for (int a(0); a < vec.size() - 1; ++a)
            {
                for (int b(a + 1); b < vec.size(); ++b)
                {
                }
            }
        }
        ++it;
    }
}

FilO::FilO(FilOConfig &config, QObject *parent)
    : QObject{parent},
    config(config)
{
    setTypeModel(new JWQTTemplateModel<TypeObject, QString>("type"));
    setSuffixModel(new JWQTTemplateModel<SuffixObject, QString>("suffix"));
    setFileModel(new JWQTTemplateModel<FileObject, QString>("file"));

    FileLoadWorker *flw(new FileLoadWorker(config.rootFilePath()));
    flw->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, flw, &QObject::deleteLater);
    connect(this, &FilO::loadFiles, flw, &FileLoadWorker::doLoad);
    connect(flw, &FileLoadWorker::resultReady, this, &FilO::handleResults);
    workerThread.start();
}

FilO::~FilO()
{
    workerThread.quit();
    workerThread.wait();
}

void FilO::init()
{
    emit loadFiles();
}

void FilO::typeClicked(const QString &id)
{
    TypeObject *to(typeModel()->getById(id));
    if (!to)
    {
        return;
    }
    suffixModel()->clear();
    auto it(to->suffix2FileInfo.begin());
    while (it != to->suffix2FileInfo.end())
    {
        SuffixObject *so(new SuffixObject);
        so->setId(it.key());
        suffixModel()->append(so);
        for (int i(0); i < it.value().size(); ++i)
        {
            so->addFileInfo(it.value()[i]);
        }
        ++it;
    }

}

void FilO::suffixClicked(const QString &id)
{
    SuffixObject *so(suffixModel()->getById(id));
    if (!so)
    {
        return;
    }
    fileModel()->clear();
    auto it(so->fileInfos.begin());
    while (it != so->fileInfos.end())
    {
        FileObject *fo(new FileObject);
        QFileInfo *fi(*it);
        fo->setId(fi->absoluteFilePath());
        fo->setFileNameWithoutExtension(fi->fileName());
        fo->setRelativePath(extractRelativePath(*fi));
        fo->setCreated(fi->birthTime());
        fo->setChanged(fi->lastModified());
        fileModel()->append(fo);
        ++it;
    }
    sortFilesByDateTime();
    findDuplicates(id);
}

void FilO::imageToClibboard(const QString &fullFilename)
{
    QMimeData *md(new QMimeData);
    QImage image(fullFilename);
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    md->setData(QStringLiteral("image/png"), arr);
    QClipboard *cb(QGuiApplication::clipboard());
    cb->setMimeData(md);
}

void FilO::sortFilesByDateTime()
{
    fileModel()->sort([](const FileObject &a, const FileObject &b)
                      {
        return a.changed() < b.changed();
    });
}

FileObject *FilO::getByIndex(int index)
{
    return fileModel()->getObject(index);
}

int FilO::yearOfDateTime(const QDateTime &dt) const
{
    return dt.date().year();
}

QString FilO::ddMMOfDateTime(const QDateTime &dt) const
{
    return dt.date().toString("dd.MM.");
}

QString FilO::extractRelativePath(const QFileInfo &fi) const
{
    QString rp(fi.path());
    rp.remove(0, config.rootFilePath().size());
    return rp;
}

void FilO::handleResults(QFileInfo *fi)
{
    allFiles.append(fi);
    setTotalFileCount(allFiles.size());
    QString suffix(fi->suffix().toLower());
    suffix2Size2FileInfos[suffix][fi->size()].push_back(fi);
    QString type(suffix2type(suffix));
    TypeObject *to(typeModel()->getById(type));
    if (!to)
    {
        to = new TypeObject;
        to->setId(type);
        typeModel()->append(to);
    }
    to->addFileInfo(suffix, allFiles.last());
}

