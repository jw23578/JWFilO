#include "suffixobject.h"

SuffixObject::SuffixObject(QObject *parent)
    : JWQTObjectInterface{parent}
{}

void SuffixObject::assign(const SuffixObject &other)
{
    setId(other.id());
}

void SuffixObject::addFileInfo(QFileInfo *fi)
{
    fileInfos.append(fi);
    setCount(fileInfos.size());
}
