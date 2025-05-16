#include "fileobject.h"
#include <QQmlEngine>

FileObject::FileObject(QObject *parent)
    : JWQTObjectInterface{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void FileObject::assign(const FileObject &other)
{
    setId(other.id());
    setFileNameWithoutExtension(fileNameWithoutExtension());
    setRelativePath(relativePath());
    setCreated(created());
    setChanged(changed());
}
