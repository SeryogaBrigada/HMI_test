#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <aktualizr/src/libaktualizr/primary/aktualizr.h>

int main(int argc, char *argv[])
{
    Config m_conf("/home/intel/OTA-HMI/HMI_test/aktualizr/config/sota_local.toml");
    Aktualizr m_art(m_conf);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
