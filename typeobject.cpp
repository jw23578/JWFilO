#include "typeobject.h"

TypeObject::TypeObject(QObject *parent)
    : JWQTObjectInterface{parent}
{}

void TypeObject::addFileInfo(const QString &suffix, QFileInfo *fi)
{
    suffix2FileInfo[suffix].append(fi);
    setCount(count() + 1);
}

void TypeObject::assign(const TypeObject &other)
{
    setId(other.id());
    setCount(other.count());
}
