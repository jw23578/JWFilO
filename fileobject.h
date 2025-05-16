#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <jwqtobjectinterface.h>
#include <QDateTime>

class FileObject : public JWQTObjectInterface
{
    Q_OBJECT
    JWQT_PROPERTY(QString, id, Id, "");
    JWQT_PROPERTY(QString, fileNameWithoutExtension, FileNameWithoutExtension, "");
    JWQT_PROPERTY(QString, relativePath, RelativePath, "");
    JWQT_PROPERTY(QDateTime, created, Created, );
    JWQT_PROPERTY(QDateTime, changed, Changed, );
public:
    explicit FileObject(QObject *parent = nullptr);
    void assign(const FileObject &other);
};

#endif // FILEOBJECT_H
