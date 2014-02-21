#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"
#include "texturerenderer.hpp"

#include "beziercurve.hpp"

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>
#include <QtQml>

#include <nmlib/model.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //qt-licensed types
    qmlRegisterType<BezierCurve>("CustomGeometry", 1, 0, "QtBezierCurve");

    //register types
    //could have used registeruncreatabletype instead, that would have allowed protected constructors,
    //but that makes it impossible to have strong typing of qml members, we'd have to use
    //variant instead. For that reason, we'll sacrifice the encapsulation in c++ for type safety in qml
    qmlRegisterType<nmgui::TextureRenderer>("NoiseModeler", 1, 0, "TextureRenderer");
    qmlRegisterType<nmgui::ModuleQ>("NoiseModeler", 1, 0, "Module");
    qmlRegisterType<nmgui::InputLinkQ>("NoiseModeler", 1, 0, "InputLink");
    qmlRegisterType<nmgui::OutputLinkQ>("NoiseModeler", 1, 0, "OutputLink");
    qmlRegisterType<nmgui::ModuleTypeQ>("NoiseModeler", 1, 0, "ModuleType");

    //create mockup data
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    auto fbmModuleType = typeManager.getType("fbm");
    auto addModuleType = typeManager.getType("add");
    auto demuxModuleType = typeManager.getType("demux2");
    auto debugInputModuleType = typeManager.getType("debug_input");
    auto debugOutputModuleType = typeManager.getType("debug_output");

    nm::Module fbmModule(*fbmModuleType, "myfbm");
    nm::Module fbmModule2(*demuxModuleType, "demux2");
    nm::Module AddModule(*addModuleType, "myAdd");
    nm::Module debugInputModule(*debugInputModuleType, "debugInput");
    nm::Module debugOutputModule(*debugOutputModuleType, "debugOutput");

    auto mockModule = nmgui::ModuleQ::fromModule(fbmModule);
    auto mockModule2 = nmgui::ModuleQ::fromModule(fbmModule2);
    auto mockModule3 = nmgui::ModuleQ::fromModule(AddModule);
    auto debugInputModuleQ = nmgui::ModuleQ::fromModule(debugInputModule);
    auto debugOutputModuleQ = nmgui::ModuleQ::fromModule(debugOutputModule);

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("mockModule", mockModule);
    viewer.rootContext()->setContextProperty("mockModule2", mockModule2);
    viewer.rootContext()->setContextProperty("mockModule3", mockModule3);
    viewer.rootContext()->setContextProperty("debugInput", debugInputModuleQ);
    viewer.rootContext()->setContextProperty("debugOutput", debugOutputModuleQ);

    viewer.rootContext()->setContextProperty("addModuleType", nmgui::ModuleTypeQ::fromModuleType(*addModuleType));
    viewer.rootContext()->setContextProperty("demuxModuleType", nmgui::ModuleTypeQ::fromModuleType(*demuxModuleType));

    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
