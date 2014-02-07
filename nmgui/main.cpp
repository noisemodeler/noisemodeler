#include "module.hpp"
#include "moduleinput.hpp"
#include "moduleoutput.hpp"
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
    qmlRegisterType<nmgui::Module>("NoiseModeler", 1, 0, "Module");
    qmlRegisterType<nmgui::ModuleInputQ>("NoiseModeler", 1, 0, "ModuleInput");
    qmlRegisterType<nmgui::ModuleOutputQ>("NoiseModeler", 1, 0, "ModuleOutput");

    //create mockup data
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    auto fbmModuleType = typeManager.getType("fbm");
    auto fbmModule = nm::Module::create(*fbmModuleType, "myfbm");
    nmgui::Module mockModule(fbmModule.get());
//    mockModule.setName("TestName");

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("mockModule", &mockModule);
    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
