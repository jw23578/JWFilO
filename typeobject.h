#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

#include <jwqtidobjectinterface.h>
#include <QFileInfo>

class TypeObject : public JWQTObjectInterface
{
    Q_OBJECT
    JWQT_PROPERTY(QString, id, Id, "");
    JWQT_PROPERTY(int, count, Count, 0);
public:
    explicit TypeObject(QObject *parent = nullptr);
    QMap<QString, QList<QFileInfo*>> suffix2FileInfo;
    void addFileInfo(const QString &suffix, QFileInfo *fi);
    void assign(const TypeObject &other);
};

#endif // TYPEOBJECT_H
