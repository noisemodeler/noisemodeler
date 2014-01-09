#include "module.h"

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //register types
    qmlRegisterType<nmgui::Module>("NoiseModeler", 1, 0, "Module");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    //create mockup data
    nmgui::Module mockModule;
    mockModule.setName("TestName");
    viewer.rootContext()->setContextProperty("mockModule", &mockModule);

    return app.exec();
}
