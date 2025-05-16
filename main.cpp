#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "filo.h"
#include "colors.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    Colors colors;
    colors.setDarkDefaults();
    FilOConfig config("");
    config.setRootFilePath("/media/jw78/AndreasBackup");
    config.setRootFilePath("/home/jw78/temp/AndreasStick3");
    FilO filo(config);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("FILO", QVariant::fromValue(&filo));
    engine.rootContext()->setContextProperty("CONFIG", QVariant::fromValue(&config));
    engine.rootContext()->setContextProperty("COLORS", QVariant::fromValue(&colors));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("JWFilO", "Main");

    filo.init();

    return app.exec();
}
