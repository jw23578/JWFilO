#ifndef FILO_H
#define FILO_H

#include <QObject>
#include "filoconfig.h"
#include <QDir>
#include "typeobject.h"
#include "suffixobject.h"
#include "fileobject.h"
#include "jwqttemplatemodel.h"
#include <QThread>

class FilO : public QObject
{
    Q_OBJECT
    QThread workerThread;
    JWQT_PROPERTY(int, totalFileCount, TotalFileCount, 0);
    JWQT_PROPERTY(JWQT_SINGLE_ARG2(JWQTTemplateModel<TypeObject, QString>*), typeModel, TypeModel, 0);
    JWQT_PROPERTY(JWQT_SINGLE_ARG2(JWQTTemplateModel<SuffixObject, QString>*), suffixModel, SuffixModel, 0);
    JWQT_PROPERTY(JWQT_SINGLE_ARG2(JWQTTemplateModel<FileObject, QString>*), fileModel, FileModel, 0);
    JWQT_PROPERTY(FileObject*, theCurrentFile, TheCurrentFile, 0)

    QString extractRelativePath(const QFileInfo &fi) const;

    FilOConfig &config;
    QMap<QString, QString> knownSufix2Types{{"pdf", "document"},
                                            {"doc", "document"},
                                            {"docx", "document"},
                                            {"jpg", "image"},
                                            {"png", "image"},
                                            {"jpeg", "image"},
                                            {"mov", "video"},
                                            {"3com", "other"},
                                            {"unknown", "unknown"}};    
    QString suffix2type(const QString &suffix) const;
    QList<QFileInfo*> allFiles;
    QMap<QString, QMap<qint64, QVector<QFileInfo*>>> suffix2Size2FileInfos;
    void loadAllFiles(const QDir &d);
    void findDuplicates(const QString &suffix);
public:
    explicit FilO(FilOConfig &config, QObject *parent = nullptr);
    ~FilO();

    void init();

    Q_INVOKABLE void typeClicked(const QString &id);
    Q_INVOKABLE void suffixClicked(const QString &id);
    Q_INVOKABLE void imageToClibboard(const QString &fullFilename);

    Q_INVOKABLE void sortFilesByDateTime();

    Q_INVOKABLE FileObject *getByIndex(int index);
    Q_INVOKABLE int yearOfDateTime(const QDateTime &dt) const;
    Q_INVOKABLE QString ddMMOfDateTime(const QDateTime &dt) const;
public slots:
    void handleResults(QFileInfo *fi);
signals:
    void loadFiles();
};

#endif // FILO_H
