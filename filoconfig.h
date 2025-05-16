#ifndef FILOCONFIG_H
#define FILOCONFIG_H

#include "jwqt_macros.h"
#include <QObject>
#include <QString>
#include <QColor>

class FilOConfig: public QObject
{
    Q_OBJECT
    JWQT_PROPERTY(QString, rootFilePath, RootFilePath, "")
    JWQT_PROPERTY(int, margins, Margins, 5)
    JWQT_PROPERTY(int, radius, Radius, 9)

public:
    FilOConfig(const QString &configFilename);
};

#endif // FILOCONFIG_H
