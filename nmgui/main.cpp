#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"
#include "graphq.hpp"
#include "typemanagerq.hpp"
#include "texturerenderer.hpp"
#include "heightmap3dexplorer.hpp"
#include "heightmaptextureexplorer.hpp"

#include "beziercurve.hpp"

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>
#include <QtQml>

#include <nmlib/model.hpp>

int main(int argc, char *argv[])
{
    //we're setting locale to english because we want to avoid
    //weird settings for commas etc messing up parsing of numbers
    QLocale::setDefault(QLocale(QLocale::English));

    QGuiApplication app(argc, argv);

    //qt-licensed types
    qmlRegisterType<BezierCurve>("CustomGeometry", 1, 0, "QtBezierCurve");

    //register types
    //could have used registeruncreatabletype instead, that would have allowed protected constructors,
    //but that makes it impossible to have strong typing of qml members, we'd have to use
    //variant instead. For that reason, we'll sacrifice the encapsulation in c++ for type safety in qml
    qmlRegisterType<nmgui::TextureRenderer>("NoiseModeler", 1, 0, "TextureRenderer");
    qmlRegisterType<nmgui::HeightMapFunction>("NoiseModeler", 1, 0, "HeightMapFunction");
    qmlRegisterType<nmgui::HeightMap3DExplorer>("NoiseModeler", 1, 0, "HeightMap3DExplorer");
    qmlRegisterType<nmgui::HeightMapTextureExplorer>("NoiseModeler", 1, 0, "HeightMapTextureExplorer");
    qmlRegisterType<nmgui::ModuleQ>("NoiseModeler", 1, 0, "Module");
    qmlRegisterType<nmgui::InputLinkQ>("NoiseModeler", 1, 0, "InputLink");
    qmlRegisterType<nmgui::OutputLinkQ>("NoiseModeler", 1, 0, "OutputLink");
    qmlRegisterType<nmgui::ModuleTypeQ>("NoiseModeler", 1, 0, "ModuleType");
    qmlRegisterType<nmgui::GraphQ>("NoiseModeler", 1, 0, "Graph");
    qmlRegisterType<nmgui::TypeManagerQ>("NoiseModeler", 1, 0, "TypeManager");

    //create mockup data
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    auto debugInputModuleType = typeManager.getType("debug_input");
    auto debugOutputModuleType = typeManager.getType("debug_output");

    nm::Graph graph{};
    auto debugInputModule = graph.createModule(*debugInputModuleType, "debugInput");
    auto debugOutputModule = graph.createModule(*debugOutputModuleType, "debugOutput");
    auto fbmModule = graph.createModule(*typeManager.getBuiltinType("fbm2"));
    debugInputModule->getOutput("pos")->addLink(*fbmModule->getInput("pos"));
    fbmModule->getOutput("result")->addLink(*debugOutputModule->getInput("height"));

    //mock user type
    {
        auto mockUserType = make_unique<nm::ModuleType>("MyMockUserType", "Long mock description that is very long");
        typeManager.addUserType(std::move(mockUserType));
    }
    {
        auto mockUserType = make_unique<nm::ModuleType>("UserType2", "Long mock description that is very long");
        typeManager.addUserType(std::move(mockUserType));
    }

    //wrapping into QObjects
    auto debugInputModuleQ = nmgui::ModuleQ::fromModule(*debugInputModule);
    auto debugOutputModuleQ = nmgui::ModuleQ::fromModule(*debugOutputModule);
    auto mockGraph = nmgui::GraphQ::fromGraph(graph);

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("debugInput", debugInputModuleQ);
    viewer.rootContext()->setContextProperty("debugOutput", debugOutputModuleQ);
    viewer.rootContext()->setContextProperty("mockGraph", mockGraph);
    viewer.rootContext()->setContextProperty("typeManager", nmgui::TypeManagerQ::fromTypeManager(typeManager));

    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
