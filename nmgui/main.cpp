#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"
#include "graphq.hpp"
#include "typemanagerq.hpp"
#include "texturerenderer.hpp"
#include "heightmap3dexplorer.hpp"
#include "heightmaptextureexplorer.hpp"
#include "document.hpp"

#include "beziercurve.hpp"

#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QQmlContext>
#include <QtQml>

#include <nmlib/model.hpp>
#include <nmlib/serialization.hpp>

#include <sstream>

int main(int argc, char *argv[])
{
    //we're setting locale to english because we want to avoid
    //weird settings for commas etc messing up parsing of numbers
    QLocale::setDefault(QLocale(QLocale::English));

    QGuiApplication app(argc, argv);
    Q_INIT_RESOURCE(nmgui);

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

    QStringList cmdLineArgs = QCoreApplication::arguments();

    QString docPath = ":/empty.nmlang.json";
    if(cmdLineArgs.count()>1){
        docPath = cmdLineArgs.at(1);
    }
    nmgui::Document document(docPath);

    //TODO this part should be handled by GUI
    //wire up debug modules
    auto typeManager = document.typeManager()->typeManager();
    auto terrainModule = typeManager->getUserType("terrain");
    auto graph = terrainModule->getGraph();
    auto debugInputModuleType = typeManager->getType("debug_input");
    auto debugOutputModuleType = typeManager->getType("debug_output");
    auto debugInputModule = graph->createModule(*debugInputModuleType, "debugInput");
    auto debugOutputModule = graph->createModule(*debugOutputModuleType, "debugOutput");
    debugInputModule->getOutput("pos")->addLink(*graph->getModule("inputs")->getInput("pos"));
    graph->getModule("outputs")->getOutput("height")->addLink(*debugOutputModule->getInput("height"));

    //wrapping into QObjects
    auto debugInputModuleQ = nmgui::ModuleQ::fromModule(*debugInputModule);
    auto debugOutputModuleQ = nmgui::ModuleQ::fromModule(*debugOutputModule);


    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("debugInput", debugInputModuleQ);
    viewer.rootContext()->setContextProperty("debugOutput", debugOutputModuleQ);
    viewer.rootContext()->setContextProperty("document", &document);

    viewer.setMainQmlFile(QStringLiteral("qml/noisemodeler/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
