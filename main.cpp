#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QScreen>

#include "provider.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Sachertorte");
    QCoreApplication::setApplicationVersion("1.0");
    QGuiApplication app(argc, argv);

    qmlRegisterType<Provider>("qt.provider", 1, 0, "Provider");

    QQmlApplicationEngine engine;

    /* This is just for scaling down for testing UI on desktop */
    if ((QGuiApplication::primaryScreen()->orientation() == Qt::PortraitOrientation && QGuiApplication::primaryScreen()->availableSize().width() < 1487) ||
            (QGuiApplication::primaryScreen()->orientation() == Qt::LandscapeOrientation && QGuiApplication::primaryScreen()->availableSize().height() < 1487)) {
        engine.rootContext()->setContextProperty("applicationScale", 0.6);
    }
    else {
        engine.rootContext()->setContextProperty("applicationScale", 1.0);
    }

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
