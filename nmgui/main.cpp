#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "texturerenderer.hpp"

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>
#include <QtQml>

#include <nmlib/model.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //register types
    qmlRegisterType<nmgui::TextureRenderer>("NoiseModeler", 1, 0, "TextureRenderer");
    qmlRegisterType<nmgui::ModuleQ>("NoiseModeler", 1, 0, "Module");
    qmlRegisterType<nmgui::InputLinkQ>("NoiseModeler", 1, 0, "ModuleInput");
    qmlRegisterType<nmgui::OutputLinkQ>("NoiseModeler", 1, 0, "ModuleOutput");

    //create mockup data
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    auto fbmModuleType = typeManager.getType("fbm");
    auto fbmModule = nm::Module::create(*fbmModuleType, "myfbm");
    auto fbmModule2 = nm::Module::create(*fbmModuleType, "myfbm2");
    auto mockModule = nmgui::ModuleQ::fromModule(*fbmModule);
    auto mockModule2 = nmgui::ModuleQ::fromModule(*fbmModule2);
//    mockModule.setName("TestName");

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("mockModule", mockModule);
    viewer.rootContext()->setContextProperty("mockModule2", mockModule2);
    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
