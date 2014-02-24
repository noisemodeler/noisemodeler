#ifndef NMGUI_TYPEMANAGERQ_HPP
#define NMGUI_TYPEMANAGERQ_HPP

#include <nmlib/util/signals.hpp>

#include <QObject>
#include <QtQml/QQmlListProperty>

namespace nm {
class TypeManager;
}

namespace nmgui {

class ModuleTypeQ;

class TypeManagerQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleTypeQ> builtinTypes READ builtinTypes CONSTANT)
public:
    explicit TypeManagerQ(nm::TypeManager *typeManager = nullptr, QObject *parent = 0);
    static TypeManagerQ *fromTypeManager(nm::TypeManager &typeManager);

    QQmlListProperty<ModuleTypeQ> builtinTypes();

private:
    nm::TypeManager *m_typeManager;

    boost::signals2::scoped_connection typeManagerDestroyedConnection;

    static ModuleTypeQ* builtinModuleAt(QQmlListProperty<ModuleTypeQ> *list, int index);
    static int builtinModulesCount(QQmlListProperty<ModuleTypeQ> *list);
};

} // namespace nmgui

#endif // NMGUI_TYPEMANAGERQ_HPP
