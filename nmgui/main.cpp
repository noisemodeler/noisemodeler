#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"
#include "graphq.hpp"
#include "typemanagerq.hpp"
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
    qmlRegisterType<nmgui::GraphQ>("NoiseModeler", 1, 0, "Graph");
    qmlRegisterType<nmgui::TypeManagerQ>("NoiseModeler", 1, 0, "TypeManager");

    //create mockup data
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
//    auto fbmModuleType = typeManager.getType("fbm");
    auto addModuleType = typeManager.getType("add");
    auto demuxModuleType = typeManager.getType("demux2");
    auto debugInputModuleType = typeManager.getType("debug_input");
    auto debugOutputModuleType = typeManager.getType("debug_output");

    nm::Graph graph{};
    graph.createModule(*demuxModuleType, "demux");
    graph.createModule(*addModuleType, "add");
    auto debugInputModule = graph.createModule(*debugInputModuleType, "debugInput");
    auto debugOutputModule = graph.createModule(*debugOutputModuleType, "debugOutput");

    //wrapping into QObjects
    auto debugInputModuleQ = nmgui::ModuleQ::fromModule(*debugInputModule);
    auto debugOutputModuleQ = nmgui::ModuleQ::fromModule(*debugOutputModule);

    auto mockGraph = nmgui::GraphQ::fromGraph(graph);

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("debugInput", debugInputModuleQ);
    viewer.rootContext()->setContextProperty("debugOutput", debugOutputModuleQ);

    viewer.rootContext()->setContextProperty("mockGraph", mockGraph);

//    viewer.rootContext()->setContextProperty("addModuleType", nmgui::ModuleTypeQ::fromModuleType(*addModuleType));
//    viewer.rootContext()->setContextProperty("demuxModuleType", nmgui::ModuleTypeQ::fromModuleType(*demuxModuleType));
    viewer.rootContext()->setContextProperty("typeManager", nmgui::TypeManagerQ::fromTypeManager(typeManager));

    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
