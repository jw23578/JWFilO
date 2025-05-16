#ifndef SUFFIXOBJECT_H
#define SUFFIXOBJECT_H

#include <jwqtobjectinterface.h>
#include <QFileInfo>

class SuffixObject : public JWQTObjectInterface
{
    Q_OBJECT
    JWQT_PROPERTY(QString, id, Id, "")
    JWQT_PROPERTY(int, count, Count, 0);
public:
    explicit SuffixObject(QObject *parent = nullptr);
    ~SuffixObject() {}
    QList<QFileInfo*> fileInfos;

    void assign(const SuffixObject &other);

    void addFileInfo(QFileInfo *fi);
};

#endif // SUFFIXOBJECT_H
