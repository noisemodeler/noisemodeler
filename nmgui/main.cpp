#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduletypeq.hpp"
#include "moduleinputq.hpp"
#include "moduleoutputq.hpp"
#include "graphq.hpp"
#include "typemanagerq.hpp"
#include "heightmap3dexplorer.hpp"
#include "heightmaptextureexplorer.hpp"
#include "document.hpp"
#include "core.hpp"

#include "beziercurve.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

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
    QCoreApplication::setApplicationName("Noise Modeler");

    QGuiApplication app(argc, argv);

    //qt-licensed types
    qmlRegisterType<BezierCurve>("CustomGeometry", 1, 0, "QtBezierCurve");

    //register types
    //could have used registeruncreatabletype instead, that would have allowed protected constructors,
    //but that makes it impossible to have strong typing of qml members, we'd have to use
    //variant instead. For that reason, we'll sacrifice the encapsulation in c++ for type safety in qml
    qmlRegisterType<nmgui::HeightMapFunction>("NoiseModeler", 1, 0, "HeightMapFunction");
    qmlRegisterType<nmgui::HeightMap3DExplorer>("NoiseModeler", 1, 0, "HeightMap3DExplorer");
    qmlRegisterType<nmgui::HeightMapTextureExplorer>("NoiseModeler", 1, 0, "HeightMapTextureExplorer");
    qmlRegisterUncreatableType<nmgui::ModuleQ>("NoiseModeler", 1, 0, "Module","uncreatable");
    qmlRegisterUncreatableType<nmgui::InputLinkQ>("NoiseModeler", 1, 0, "InputLink","uncreatable");
    qmlRegisterUncreatableType<nmgui::OutputLinkQ>("NoiseModeler", 1, 0, "OutputLink","uncreatable");
    qmlRegisterUncreatableType<nmgui::ModuleInputQ>("NoiseModeler", 1, 0, "ModuleInput","uncreatable");
    qmlRegisterUncreatableType<nmgui::ModuleOutputQ>("NoiseModeler", 1, 0, "ModuleOutput","uncreatable");
    qmlRegisterUncreatableType<nmgui::ModuleTypeQ>("NoiseModeler", 1, 0, "ModuleType","uncreatable");
    qmlRegisterUncreatableType<nmgui::GraphQ>("NoiseModeler", 1, 0, "Graph","uncreatable");
    qmlRegisterUncreatableType<nmgui::TypeManagerQ>("NoiseModeler", 1, 0, "TypeManager","uncreatable");

    QStringList cmdLineArgs = QCoreApplication::arguments();

    QString docPath = ":/empty.nm.json";
    if(cmdLineArgs.count()>1){
        docPath = cmdLineArgs.at(1);
    }
    nmgui::Document document(docPath);
    nmgui::Core core;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("document", &document);
    engine.rootContext()->setContextProperty("core", &core);
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
