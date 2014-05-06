#include "graphq.hpp"

#include <nmlib/model/graph.hpp>
#include <nmlib/model/module.hpp>

#include "moduleq.hpp"
#include "moduletypeq.hpp"

namespace nmgui {

GraphQ::GraphQ(nm::Graph *graph, QObject *parent) :
    QObject(parent),
    m_graph(graph)
{
    Q_ASSERT(m_graph!=nullptr);
    Q_ASSERT(m_graph->getUserData()==nullptr);
    m_graph->setUserData(this);

    m_graphDestroyedConnection = m_graph->destroying.connect([&](nm::Graph &){
        deleteLater();
        m_graph->setUserData(nullptr);
        m_graph = nullptr;
    });

    m_moduleAddedConnection = m_graph->moduleAdded.connect([&](nm::Graph&, nm::Module &module, unsigned int index){
        moduleAdded(ModuleQ::fromModule(module), index);
        modulesChanged();
    });
    m_moduleRemovedConnection = m_graph->moduleRemoved.connect([&](nm::Graph&, nm::Module &module, unsigned int index){
        moduleRemoved(ModuleQ::fromModule(module), index);
        modulesChanged();
    });
}

GraphQ *GraphQ::fromGraph(nm::Graph &graph)
{
    auto userData = static_cast<GraphQ*>(graph.getUserData());
    return userData != nullptr ? userData : new GraphQ(&graph);
}

QQmlListProperty<ModuleQ> GraphQ::modules()
{
    return QQmlListProperty<ModuleQ>(this, 0, nullptr, &GraphQ::modulesCount, &GraphQ::moduleAt, nullptr);
}

void GraphQ::createModule(ModuleTypeQ *type, QString name)
{
    /*auto module =*/ m_graph->createModule(*type->moduleType(), name.toStdString());
    //    return module ? ModuleQ::fromModule(*module) : nullptr;
}

void GraphQ::createModule(ModuleTypeQ *type)
{
    m_graph->createModule(*type->moduleType());
}

void GraphQ::removeModule(ModuleQ *module)
{
    m_graph->removeModule(*module->module());
}

ModuleQ *GraphQ::findModule(QString name)
{
    auto modulePtr = m_graph->getModule(name.toStdString());
    return modulePtr ? ModuleQ::fromModule(*modulePtr) : nullptr;
}

ModuleQ *GraphQ::moduleAt(QQmlListProperty<ModuleQ> *list, int index)
{
    GraphQ *graph = qobject_cast<GraphQ *>(list->object);
    if(graph){
        return ModuleQ::fromModule(*graph->m_graph->getModule(index));
    } else {
        return nullptr;
    }
}

int GraphQ::modulesCount(QQmlListProperty<ModuleQ> *list)
{
    GraphQ *graph = qobject_cast<GraphQ *>(list->object);
    if(graph){
        return graph->m_graph->numModules();
    } else {
        return 0;
    }
}


} // namespace nmgui
