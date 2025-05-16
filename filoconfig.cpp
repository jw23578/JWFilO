#include "filoconfig.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

FilOConfig::FilOConfig(const QString &configFilename):QObject(0)
{
    QFile loadFile(configFilename);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }
    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject config(loadDoc.object());
    setRootFilePath(config[rootFilePathName].toString());
}
