#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>
#include <QDomNode>

#include "includes/documenthandler.h"
#include "includes/storageinterface.h"
#include "includes/imagebaseconverter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<DocumentHandler>("net.spencer.dochandle", 1, 0, "DocumentHandler");
    qmlRegisterType<StorageInterface>("net.spencer.storage", 1, 0, "StorageInterface");
    qmlRegisterType<ImageBaseConverter>("net.spencer.image", 1, 0, "ImageToString64");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/gui/main.qml")));

    QFontDatabase fontDatabase;
    if (fontDatabase.addApplicationFont(":/fonts/fontello.ttf") == -1)
        qWarning() << "Failed to load fontello.ttf";

    return app.exec();
}
