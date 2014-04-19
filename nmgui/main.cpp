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

#include <sstream>

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

    //mock user type
    {
        auto mockUserType = make_unique<nm::ModuleType>("Terrain", "Long mock description that is very long");
        typeManager.addUserType(std::move(mockUserType));
    }

    //create mock inputs/outputs
    auto terrainModule = typeManager.getUserType("Terrain");
    terrainModule->addInput("position", nm::SignalType{2});
    terrainModule->addOutput("height", nm::SignalType{1});
    auto graph = terrainModule->getGraph();

    //populate the mock graph with only fbm terrain
    auto fbmModule = graph->createModule(*typeManager.getBuiltinType("fbm2"));
    graph->getModule("inputs")->getOutput("position")->addLink(*fbmModule->getInput("pos"));
    fbmModule->getOutput("result")->addLink(*graph->getModule("outputs")->getInput("height"));

    //wire up debug modules
    auto debugInputModuleType = typeManager.getType("debug_input");
    auto debugOutputModuleType = typeManager.getType("debug_output");
    auto debugInputModule = graph->createModule(*debugInputModuleType, "debugInput");
    auto debugOutputModule = graph->createModule(*debugOutputModuleType, "debugOutput");
    debugInputModule->getOutput("pos")->addLink(*graph->getModule("inputs")->getInput("position"));
    graph->getModule("outputs")->getOutput("height")->addLink(*debugOutputModule->getInput("height"));

    //add some more types to have some mock data
    for(int i=0; i<2; ++i) {
        std::stringstream ss;
        ss << "UserType" << i;
        auto mockUserType = make_unique<nm::ModuleType>(ss.str(), "Long mock description that is very long");
        typeManager.addUserType(std::move(mockUserType));
    }
    typeManager.getUserType("UserType0")->addInput("position", nm::SignalType{2});
    typeManager.getUserType("UserType0")->addOutput("humidity", nm::SignalType{1});

    //wrapping into QObjects
    auto debugInputModuleQ = nmgui::ModuleQ::fromModule(*debugInputModule);
    auto debugOutputModuleQ = nmgui::ModuleQ::fromModule(*debugOutputModule);
//    auto mockGraph = nmgui::GraphQ::fromGraph(graph);

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("debugInput", debugInputModuleQ);
    viewer.rootContext()->setContextProperty("debugOutput", debugOutputModuleQ);
//    viewer.rootContext()->setContextProperty("mockGraph", mockGraph);
    viewer.rootContext()->setContextProperty("typeManager", nmgui::TypeManagerQ::fromTypeManager(typeManager));

    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
