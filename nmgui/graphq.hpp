#ifndef NMGUI_GRAPHQ_HPP
#define NMGUI_GRAPHQ_HPP

#include <nmlib/util/signals.hpp>

#include <QObject>
#include <QtQml/QQmlListProperty>

namespace nm {
class Graph;
}

namespace nmgui {

class ModuleQ;
class ModuleTypeQ;

class GraphQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleQ> modules READ modules NOTIFY modulesChanged)
public:
    explicit GraphQ(nm::Graph *graph = nullptr, QObject *parent = 0);
    static GraphQ *fromGraph(nm::Graph &graph);

    QQmlListProperty<ModuleQ> modules();

    Q_INVOKABLE void createModule(nmgui::ModuleTypeQ *type, QString name);
    Q_INVOKABLE void createModule(nmgui::ModuleTypeQ *type);

signals:
    void modulesChanged();

private:
    nm::Graph *m_graph;
    boost::signals2::scoped_connection m_graphDestroyedConnection;
    boost::signals2::scoped_connection m_moduleAddedConnection;
    boost::signals2::scoped_connection m_moduleRemovedConnection;
    static ModuleQ *moduleAt(QQmlListProperty<ModuleQ> *list, int index);
    static int modulesCount(QQmlListProperty<ModuleQ> *list);
};

} // namespace nmgui

#endif // NMGUI_GRAPHQ_HPP
